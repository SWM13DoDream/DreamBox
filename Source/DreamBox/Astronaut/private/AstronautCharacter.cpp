// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/AstronautCharacter.h"
#include "../public/TimerWidget.h"
#include "../public/MissionWidget.h"
#include "../public/DialogController.h"
#include "../public/AstronautGamemode.h"
#include "../public/GamemodeArbiter.h"
#include "../public/MissionSelectionPanel.h"
#include "../../../../../Plugins/Runtime/CableComponent/Source/CableComponent/Classes/CableComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAstronautCharacter::AAstronautCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->Tags = { "Player" };

	InfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INFO_WIDGET"));
	InfoWidget->SetupAttachment(FollowingCamera);
	InfoWidget->SetHiddenInGame(true);

	DialogController = CreateDefaultSubobject<UChildActorComponent>(TEXT("DIALOG_WIDGET"));
	DialogController->SetupAttachment(FollowingCamera);

	TimerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TIMER_WIDGET"));
	TimerWidget->SetupAttachment(VROrigin);
	TimerWidget->SetHiddenInGame(true);

	MissionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MISSION_WIDGET"));
	MissionWidget->SetupAttachment(VROrigin);
	MissionWidget->SetHiddenInGame(true);

	SelectedMission = EAstronautMissionType::CSM;
	MoveType = EAstronautCSMMoveType::IVA;

	// IVA �̵� ���� �Ķ���� �⺻��
	IVAGripRadius = 30.0f;
	IVAPullingForceMultiplier = 3000.0f;
	IVAPushingForceMultiplier = 9000.0f;
	IVAPullingForceDecrementInterval = 60;

	// EVA�� �ʿ��� ĳ���� ���� ���̺� (�⺻������ ��Ȱ��ȭ�� ����)
	Cable = CreateDefaultSubobject<UCableComponent>(TEXT("CABLE"));
	Cable->SetupAttachment(VROrigin);
	Cable->SetHiddenInGame(true);

	// EVA �̵� ���� �Ķ���� �⺻��
	EVACharacterHeight = 40.0f;
	EVAGripRadius = 75.0f;
	EVAPullingForceMultiplier = 3000.0f;
	EVAPullingForceDecrementInterval = 60;
	EVAHookForce = 1000000.0f;
	EVAExternalForceMagnitude = 12000.0f;
	EVACableMaxLength = 1500.0f;
}

// Called when the game starts or when spawned
void AAstronautCharacter::BeginPlay()
{
	Super::BeginPlay();
	Movement = this->GetCharacterMovement();
	bMovable = false;
	bIsWaitingPlayer = false;
}

// Called to bind functionality to input
void AAstronautCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAstronautCharacter::OnInteract);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AAstronautCharacter::ReleaseInteract);

	// �߰� �Է� : ����
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AAstronautCharacter::OnSpecialKey);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &AAstronautCharacter::ReleaseSpecialKey);
}

void AAstronautCharacter::MoveForward(float Value)
{
	if (bMovable && SelectedMission == EAstronautMissionType::LEM)
	{
		FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAstronautCharacter::MoveRight(float Value)
{
	if (bMovable && SelectedMission == EAstronautMissionType::LEM)
	{
		FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AAstronautCharacter::OnSpecialKey()
{
	if (bMovable)
	{
		if (SelectedMission == EAstronautMissionType::LEM) Jump();
		else if (MoveType == EAstronautCSMMoveType::EVA) ControlHook();
	}
}

void AAstronautCharacter::ReleaseSpecialKey()
{
	if (SelectedMission == EAstronautMissionType::LEM)
	{
		StopJumping();
	}
}

void AAstronautCharacter::OnInteract()
{
	WidgetInteraction->PressPointerKey(EKeys::LeftMouseButton);
}

void AAstronautCharacter::ReleaseInteract()
{
	WidgetInteraction->ReleasePointerKey(EKeys::LeftMouseButton);
}

void AAstronautCharacter::RegisterArbiter(class AGamemodeArbiter* Invoker)
{
	Arbiter = Invoker;
}

void AAstronautCharacter::CloseWaitingPanel()
{
	if (bIsWaitingPlayer)
	{
		AMissionSelectionPanel* SelectionPanel =
			Cast<AMissionSelectionPanel>(Arbiter->MissionSelectionControllable->GetActor_Implementation());

		SelectionPanel->StopWaitingPlayer();
	}
}

void AAstronautCharacter::OpenSelectMissionPanel()
{
	ENetMode NetworkingMode = GetWorld()->GetNetMode();

	if (NetworkingMode == ENetMode::NM_ListenServer)
	{
		AAstronautGamemode* Gamemode =
			Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (Gamemode->RemotePlayer == nullptr)
		{
			AMissionSelectionPanel* SelectionPanel =
				Cast<AMissionSelectionPanel>(Arbiter->MissionSelectionControllable->GetActor_Implementation());

			SelectionPanel->WaitingForPlayer(Gamemode->GetIPAddr());
			bIsWaitingPlayer = true;
		}
		else
		{
			// ���ڰ��� SetHiddenInGame�� �����ϹǷ� false�� �Ѱ� ���� �г� Ȱ��ȭ
			Arbiter->MissionSelectionControllable->SetStatus_Implementation(false);
		}
	}
	else
	{
		Arbiter->MissionSelectionControllable->SetStatus_Implementation(false);
	}
}

void AAstronautCharacter::SelectMission(int32 Mission)
{
	SelectedMission = Mission;
	ENetMode NetworkingMode = GetWorld()->GetNetMode();
	if (NetworkingMode == ENetMode::NM_ListenServer || NetworkingMode == ENetMode::NM_Client)
	{
		MakeRPCSelectMission(Mission);
	}
	else
	{
		Arbiter->MissionSelectionControllable->SetStatus_Implementation(true);
		PlayMissionInitSequence();
	}
}

void AAstronautCharacter::InitializeMission()
{
	if (SelectedMission == EAstronautMissionType::LEM)
	{
		// ���� ������ ��ġ�� Ž�缱 ���η� ĳ���� �̵�
		SetActorLocation({ -22009.0f, -25467.0f, -106513.0f });
		SetActorRotation({ 0.0f, 80.0f, 0.0f });
		Movement->GravityScale = 0.17f;

		// Ÿ�̸� �� �̼� ��Ʈ�ѷ� �ʱ�ȭ
		TimerWidget->SetHiddenInGame(false);
		MissionWidget->SetHiddenInGame(false);
		TimerController = Cast<UTimerWidget>(TimerWidget->GetWidget());
		MissionController = Cast<UMissionWidget>(MissionWidget->GetWidget());

		// 6�� �ɼ� �� 3���� �����ϴ� ���� ������ ��� (ex. 7 = 000111, 11 = 001011, 13 = 001101 ... ) 
		int32 RandomMissionIndices[] = { 7, 11, 13, 14, 19, 21, 22, 25, 26, 28, 35, 37, 38, 41, 42, 44, 49, 50, 52, 56 };
		int32 RandomMissionSelector = RandomMissionIndices[FMath::RandRange(0, 19)];

		// ���� �����ڿ� ���� bool[SUBMISSION_NUM] Ÿ���� bIsSubmissionDone�� �ʱ�ȭ �� �Ҵ�
		for (int i = 0; i < 6; i++)
		{
			if (RandomMissionSelector % 2 == 1)
			{
				bIsSubmissionDone[i] = true;

				// UnsetSubMission(i)�� ���� �ʰ� true ���ڸ� ���� ������ ���
				// true ���ڸ� interactiontrigger�� �ѱ�� ���� ���� �ÿ� �߻��ϴ� ���Ἲ ������ �ذ� ����
				Arbiter->SubInteractionControllables[i]->SetStatus_Implementation(true);
			}
			else
			{
				RandomSubmissionIndices.Add(i);
				SubMissionText.Add(Arbiter->SUB_MISSION_TEXT[i]);

				Arbiter->SubStaticMeshControllables[i]->SetStatus_Implementation(true);
			}
			RandomMissionSelector /= 2;
		}

		// ���� �̼� ���� ���� �ʱ�ȭ (���� �̼��� InitializeMissions���� ó��)
		bIsMissionDone = false;
		MainMissionText = Arbiter->MAIN_MISSION_INIT;

		// 1�ʿ� �� ���� ȣ��Ǵ� Ÿ�̸Ӹ� ����. (�ʱⰪ 5��)
		Time = 300;
		GetWorldTimerManager().SetTimer(MissionTickHandler, this, &AAstronautCharacter::MissionTick, 1.0f, true, 1.0f);

		MissionController->UpdateMainMissionDisplay();
		MissionController->UpdateSubMissionDisplay();

		// SignDisplay ����
		for (int i = 0; i < 6; i++)
		{
			if (!bIsSubmissionDone[i])
			{
				if (i < 4) Arbiter->SignDisplayControllables[i]->SetStatus_Implementation(false);
			}
			else Arbiter->SubGuideControllables[i]->SetStatus_Implementation(false);
		}
	}
	else if (SelectedMission == EAstronautMissionType::CSM)
	{
		// ���� ����� ��ġ�� �糪 ����Ʈ���� ���η� ĳ���� �̵�
		SetActorLocation({ -222951.0f, 31804.0f, 141102.0f });
		SetActorRotation({ 0.0f, 0.0f, 0.0f });

		Movement->GravityScale = 0.0f;
		RegisterHookHand();

		PullingForceDecrementCounter = 0;

		// ĳ���� ���� üũ Ÿ�̸� ���
		GetWorldTimerManager().SetTimer(ForceCheckHandler, this, &AAstronautCharacter::ForceChecker, 1.0f / 120, true, 1.0f / 120);

		// 1�ʿ� �� ���� ȣ��Ǵ� Ÿ�̸Ӹ� ����. (�ʱⰪ 5��)
		Time = 300;
		GetWorldTimerManager().SetTimer(MissionTickHandler, this, &AAstronautCharacter::MissionTick, 1.0f, true, 1.0f);
	}

	// Multiplay ���� üũ
	ENetMode NetworkingMode = GetWorld()->GetNetMode();
	bool bInMultiplay = false;
	if (NetworkingMode == NM_ListenServer)
	{
		AAstronautGamemode* Gamemode =
			Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (Gamemode->RemotePlayer != nullptr) bInMultiplay = true;
	}
	else if (NetworkingMode == NM_Client) bInMultiplay = true;

	// Dialog Controller Ȱ��ȭ
	ADialogController* Dialog = Cast<ADialogController>(DialogController->GetChildActor());
	Dialog->SetActivated(true, SelectedMission, bInMultiplay);
}

void AAstronautCharacter::DoMainMission()
{
	bIsMissionDone = true;
	MainMissionText = Arbiter->MAIN_MISSION_DONE;

	Arbiter->MainStaticMeshControllable->SetStatus_Implementation(true);
	Arbiter->MainInteractionControllable->SetStatus_Implementation(false);
	Arbiter->MainGuideControllable->SetStatus_Implementation(false);

	// �̼� ���� ���÷��� ������Ʈ
	MissionController->UpdateMainMissionDisplay();
}

void AAstronautCharacter::DoSubMission(int32 Index)
{
	bIsSubmissionDone[Index] = true;
	for (int32 i = 0; i < 3; i++)
	{
		if (RandomSubmissionIndices[i] == Index)
		{
			bIsSubmissionDone[Index] = true;
			SubMissionText[i] = Arbiter->SUB_MISSION_DONE;
		}
	}
	Arbiter->SubInteractionControllables[Index]->SetStatus_Implementation(false);

	// �̼� ���� ���÷��� ������Ʈ
	MissionController->UpdateSubMissionDisplay();

	// ���̵� ���� Visibility ����
	Arbiter->SubGuideControllables[Index]->SetStatus_Implementation(false);
}

void AAstronautCharacter::MoveLEM(bool bIsEntering)
{
	if (bIsEntering)
	{
		SetActorLocation(FVector(-22065.0f, -25610.0f, -106490.0f));
	}
	else
	{
		SetActorLocation(FVector(-21255.0f, -24510.0f, -106770.0f));
	}
}

bool AAstronautCharacter::IsAboardable()
{
	return Time <= 20 || Time >= (300 - 20);
}

void AAstronautCharacter::StartEVA()
{
	MoveType = EAstronautCSMMoveType::EVA;
		
	// ���ο� ĳ���� ���� ���
	GetCapsuleComponent()->SetCapsuleHalfHeight(EVACharacterHeight);
	FollowingCamera->SetRelativeLocation(FVector(30.0f, 0.0f, EVACharacterHeight + 3.0f));

	// ���̺� Ȱ��ȭ
	Cable->SetHiddenInGame(false);

	// ĳ���� ��ġ �̵�, �ش� ��ġ�� ���̺� ����
	SetActorLocation({ -223090.0, 31871.0, 141389.0 });
	SetActorRotation({ -EVACharacterPitch, 0.0f, 0.0f });
	RecentHookPoint = GetActorLocation();

	Movement->StopMovementImmediately();
	Movement->ClearAccumulatedForces();

	bMovable = false;
	OpenInfoWidget(FName("Hook"));
}

void AAstronautCharacter::ReturnIVA()
{
	MoveType = EAstronautCSMMoveType::IVA;

	// ������ ĳ���� ���̷� ����
	GetCapsuleComponent()->SetCapsuleHalfHeight(80.0f);
	FollowingCamera->SetRelativeLocation(FVector(30.0f, 0.0f, 83.0f));

	// ���̺� ��Ȱ��ȭ
	Cable->SetHiddenInGame(true);

	// ĳ���� ��ġ �̵�
	SetActorLocation({ -220307.0f, 31867.0f, 142149.0f });
	SetActorRotation({ 0.0f, -90.0f, 0.0f });

	// ���̺� ���� üũ Ÿ�̸� ����
	// GetWorldTimerManager().ClearTimer(TimerHandler);

	Movement->StopMovementImmediately();
	Movement->ClearAccumulatedForces();
}

void AAstronautCharacter::OnGrip(AActor* HandActor, bool bIsLeft)
{
	// Sphere Tracing�� �̿��� ���� �� �ִ� ����ƽ �޽ð� �ִ��� Ȯ��
	if (bMovable && SelectedMission == EAstronautMissionType::CSM)
	{
		FVector TraceStartLocation = HandActor->GetActorLocation();
		FVector TraceEndLocation =
			TraceStartLocation + HandActor->GetActorForwardVector();
		TArray<TEnumAsByte<EObjectTypeQuery>> TargetTypes;
		TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
		TargetTypes.Add(WorldStatic);
		TArray<AActor*> IgnoreActors;

		if (MoveType == EAstronautCSMMoveType::IVA)
		{
			FHitResult HitResult;

			bool bIsSphereTraceSucceed = UKismetSystemLibrary::SphereTraceSingleForObjects(
				GetWorld(), TraceStartLocation, TraceEndLocation, IVAGripRadius, TargetTypes,
				false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true
			);

			if (bIsSphereTraceSucceed)
			{
				Movement->StopMovementImmediately();
				Movement->ClearAccumulatedForces();
				FVector PullingForce = (TraceStartLocation - GetActorLocation()) * IVAPullingForceMultiplier;

				Movement->AddForce(PullingForce);
				RecentPullingForce = PullingForce;

				PullingForceDecrementCounter = IVAPullingForceDecrementInterval;

				if (bIsLeft)
				{
					bIsGrabbingL = true;
					RecentGrabbingPointL = TraceStartLocation - GetActorLocation();
				}
				else
				{
					bIsGrabbingR = true;
					RecentGrabbingPointR = TraceStartLocation - GetActorLocation();
				}
			}
		}
		else if (MoveType == EAstronautCSMMoveType::EVA)
		{
			TArray<FHitResult> HitResults;

			bool bIsSphereTraceSucceed = UKismetSystemLibrary::SphereTraceMultiForObjects(
				GetWorld(), TraceStartLocation, TraceEndLocation, EVAGripRadius, TargetTypes,
				false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResults, true
			);

			if (bIsSphereTraceSucceed)
			{
				for (const FHitResult Target : HitResults)
				{
					TArray<FName> Classifier = Target.Actor->Tags;
					if (Classifier.Num() > 0 && Classifier[0].ToString().Equals("HookPoint"))
					{
						Movement->StopMovementImmediately();
						Movement->ClearAccumulatedForces();
						FVector PullingForce = (TraceStartLocation - GetActorLocation()) * EVAPullingForceMultiplier;

						Movement->AddForce(PullingForce);
						RecentPullingForce = PullingForce;

						PullingForceDecrementCounter = EVAPullingForceDecrementInterval;

						if (bIsLeft)
						{
							bIsGrabbingL = true;
							RecentGrabbingPointL = TraceStartLocation - GetActorLocation();
						}
						else
						{
							bIsGrabbingR = true;
							RecentGrabbingPointR = TraceStartLocation - GetActorLocation();
						}

						break;
					}
				}
				
			}
		}
	}
}

void AAstronautCharacter::ReleaseGrip(AActor* HandActor, bool bIsLeft)
{
	if (bMovable && SelectedMission == EAstronautMissionType::CSM)
	{
		// ���� �̵��� ���, Grip Point���� �о ��ġ�� ����� ���ۿ� ���� ����
		if (MoveType == EAstronautCSMMoveType::IVA)
		{
			if (bIsLeft && bIsGrabbingL)
			{
				FVector RelativeHandLocation = HandActor->GetActorLocation() - GetActorLocation();
				bIsGrabbingL = false;
				if (!bIsGrabbingR)
				{
					FVector Diff = RecentGrabbingPointL - RelativeHandLocation;
					Movement->AddForce(Diff * IVAPushingForceMultiplier);
					PullingForceDecrementCounter = 0;
				}
			}
			else if (!bIsLeft && bIsGrabbingR)
			{
				FVector RelativeHandLocation = HandActor->GetActorLocation() - GetActorLocation();
				bIsGrabbingR = false;
				if (!bIsGrabbingL)
				{
					FVector Diff = RecentGrabbingPointR - RelativeHandLocation;
					Movement->AddForce(Diff * IVAPushingForceMultiplier);
					PullingForceDecrementCounter = 0;
				}
			}
		}
		// ���� �̵��� ���, �� ���� �� ���� ���� -y �������� ���� ���� ����
		else if (MoveType == EAstronautCSMMoveType::EVA)
		{
			if (bIsLeft && bIsGrabbingL)
			{
				bIsGrabbingL = false;
				if (!bIsGrabbingR)
				{
					Movement->AddForce(FVector(0.0f, -1.0f, 0.3f) * EVAExternalForceMagnitude);
					PullingForceDecrementCounter = 0;
					OpenInfoWidget(FName("Rewind"));
				}
			}
			else if (!bIsLeft && bIsGrabbingR)
			{
				bIsGrabbingR = false;
				if (!bIsGrabbingL)
				{
					Movement->AddForce(FVector(0.0f, -1.0f, 0.3f) * EVAExternalForceMagnitude);
					PullingForceDecrementCounter = 0;
					OpenInfoWidget(FName("Rewind"));
				}
			}
		}
	}
}

void AAstronautCharacter::ControlHook()
{
	FVector TraceStartLocation = HookHand->GetActorLocation();
	FVector TraceEndLocation =
		TraceStartLocation + HookHand->GetActorForwardVector();
	TArray<TEnumAsByte<EObjectTypeQuery>> TargetTypes;
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	TargetTypes.Add(WorldStatic);

	// Default parameters
	TArray<AActor*> IgnoreActors;
	TArray<FHitResult> HitResults;

	bool bIsSphereTraceSucceed = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(), TraceStartLocation, TraceEndLocation, EVAGripRadius, TargetTypes,
		false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResults, true
	);

	// �������� ������ �κ��� ã�� ��� �� ���� ���ο� ���������� ����
	if (bIsSphereTraceSucceed)
	{
		for (const FHitResult Target : HitResults)
		{
			TArray<FName> Classifier = Target.Actor->Tags;
			if (Classifier.Num() > 0 && Classifier[0].ToString().Equals("HookPoint"))
			{
				RecentHookPoint = Target.ImpactPoint;
				return;
			}
		}
	}

	// ������� ����� ��� �������� ���� ������ ���� ���� ����
	Movement->StopMovementImmediately();
	Movement->ClearAccumulatedForces();

	FVector DirectionVector = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), RecentHookPoint);
	Movement->AddForce(DirectionVector * EVAHookForce);
}

void AAstronautCharacter::MissionTick()
{
	Time -= 1;
	if (Time < 0) Time = 300;

	if (TimerController != nullptr) TimerController->UpdateDisplay();
}

void AAstronautCharacter::ForceChecker()
{
	if (PullingForceDecrementCounter > 0)
	{
		FVector CounterForce = (MoveType == EAstronautCSMMoveType::IVA) ?
			-RecentPullingForce / IVAPullingForceDecrementInterval
			: -RecentPullingForce / EVAPullingForceDecrementInterval;

		Movement->AddForce(CounterForce);
		PullingForceDecrementCounter -= 1;

		if (PullingForceDecrementCounter == 0)
		{
			Movement->StopMovementImmediately();
			Movement->ClearAccumulatedForces();
		}
	}

	if (MoveType == EAstronautCSMMoveType::EVA)
	{
		// Cable�� End Location�� ��� ��ġ�� �����Ǳ� ������ ��� ������Ʈ ���־�� ��
		Cable->EndLocation =
			UKismetMathLibrary::InverseTransformLocation(GetActorTransform(), RecentHookPoint);

		if (GetCableLength() > EVACableMaxLength)
		{
			Movement->StopMovementImmediately();
			Movement->ClearAccumulatedForces();
		}
	}
}

float AAstronautCharacter::GetCableLength()
{
	return (RecentHookPoint - GetActorLocation()).Size();
}

// =============================== //
// ��Ƽ�÷��� ���� �Լ� �������Դϴ�. //
// =============================== //

void AAstronautCharacter::OnRPCStartContent_Implementation()
{
	PlayInitialSequence();
}

void AAstronautCharacter::MakeRPCSelectMission_Implementation(int32 Mission)
{
	AAstronautGamemode* Gamemode =
		Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

	// ���� �÷��̾� ĳ����
	if (IsLocallyControlled())
	{
		if (Mission != EAstronautMissionType::NONE)
		{
			// ���� ���� ȣ��Ʈ���� �ٸ� �÷��̾� ���� �̼��� ������ ��� �׳� ����
			if (Gamemode->RemotePlayer == nullptr)
			{
				Gamemode->bInMission = true;
				Arbiter->MissionSelectionControllable->SetStatus_Implementation(true);
				PlayMissionInitSequence();
			}
			// �ٸ� �÷��̾ �����ϰ�, �װ� �̼��� ������ ��� ���� ����
			else if (Gamemode->ClientMission != EAstronautMissionType::NONE)
			{
				Gamemode->HostMission = Mission;
				Gamemode->RemotePlayer->OnRPCCheckReadyState(true, Mission);
				OnRPCCheckReadyState(true, Mission);
			}
			// �ٸ� �÷��̾ �����ϰ�, ���� �̼��� �������� ���� ��� �̼� Lock
			else
			{
				Gamemode->HostMission = Mission;
				Gamemode->RemotePlayer->OnRPCCheckReadyState(false, Mission);
			}
		}
		else
		{
			// �ٸ� �÷��̾��� �̼� Lock ����
			Gamemode->HostMission = Mission;
			Gamemode->RemotePlayer->OnRPCCheckReadyState(false, Mission);
		}
	}
	// Ŭ���̾�Ʈ �÷��̾� ĳ����
	else
	{
		if (Mission != EAstronautMissionType::NONE)
		{
			// ȣ��Ʈ �÷��̾ �̼��� ������ ��� ���� ����
			if (Gamemode->HostMission != EAstronautMissionType::NONE)
			{
				Gamemode->ClientMission = Mission;
				Gamemode->RemotePlayer->OnRPCCheckReadyState(true, Mission);
				OnRPCCheckReadyState(true, Mission);
			}
			// ȣ��Ʈ �÷��̾ ���� �̼��� �������� ���� ��� �̼� Lock
			else
			{
				Gamemode->ClientMission = Mission;
				Gamemode->LocalPlayer->OnRPCCheckReadyState(false, Mission);
			}
		}
		else
		{
			// ȣ��Ʈ �÷��̾��� �̼� Lock ����
			Gamemode->ClientMission = Mission;
			Gamemode->LocalPlayer->OnRPCCheckReadyState(false, Mission);
		}
	}
}

void AAstronautCharacter::OnRPCCheckReadyState_Implementation(bool bStartMission, int32 MissionToLock)
{
	if (bStartMission)
	{
		Arbiter->MissionSelectionControllable->SetStatus_Implementation(true);
		PlayMissionInitSequence();
	}
	else
	{
		AMissionSelectionPanel* SelectionPanel = 
			Cast<AMissionSelectionPanel>(Arbiter->MissionSelectionControllable->GetActor_Implementation());

		SelectionPanel->LockMission(MissionToLock);
	}
}