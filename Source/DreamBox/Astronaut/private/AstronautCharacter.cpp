// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/AstronautCharacter.h"
#include "../public/TimerWidget.h"
#include "../public/MissionWidget.h"
#include "../public/DialogController.h"
#include "../public/AstronautGamemode.h"
#include "../public/GamemodeArbiter.h"
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

	// IVA 이동 관련 파라미터 기본값
	IVAGripRadius = 30.0f;
	IVAPullingForceMultiplier = 3000.0f;
	IVAPushingForceMultiplier = 9000.0f;
	IVAPullingForceDecrementInterval = 60;

	// EVA에 필요한 캐릭터 고정 케이블 (기본적으로 비활성화된 상태)
	Cable = CreateDefaultSubobject<UCableComponent>(TEXT("CABLE"));
	Cable->SetupAttachment(VROrigin);
	Cable->SetHiddenInGame(true);

	// EVA 이동 관련 파라미터 기본값
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
}

// Called to bind functionality to input
void AAstronautCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAstronautCharacter::OnInteract);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AAstronautCharacter::ReleaseInteract);

	// 추가 입력 : 점프
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AAstronautCharacter::OnSpecialKey);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &AAstronautCharacter::ReleaseSpecialKey);
}

void AAstronautCharacter::MoveForward(float Value)
{
	if (SelectedMission == EAstronautMissionType::LEM)
	{
		FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AAstronautCharacter::MoveRight(float Value)
{
	if (SelectedMission == EAstronautMissionType::LEM)
	{
		FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AAstronautCharacter::OnSpecialKey()
{
	if (SelectedMission == EAstronautMissionType::LEM)
	{
		Jump();
	}
	else
	{
		if (MoveType == EAstronautCSMMoveType::EVA)
		{
			ControlHook();
		}
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

void AAstronautCharacter::InitializeMission()
{
	if (SelectedMission == EAstronautMissionType::LEM)
	{
		// 월면 기지에 위치한 탐사선 내부로 캐릭터 이동
		SetActorLocation({ -22009.0f, -25467.0f, -106513.0f });
		SetActorRotation({ 0.0f, 80.0f, 0.0f });
		Movement->GravityScale = 0.17f;

		// 타이머 및 미션 컨트롤러 초기화
		TimerController = Cast<UTimerWidget>(TimerWidget->GetWidget());
		MissionController = Cast<UMissionWidget>(MissionWidget->GetWidget());

		// 6개 옵션 중 3개를 선택하는 이진 선택자 목록 (ex. 7 = 000111, 11 = 001011, 13 = 001101 ... ) 
		int32 RandomMissionIndices[] = { 7, 11, 13, 14, 19, 21, 22, 25, 26, 28, 35, 37, 38, 41, 42, 44, 49, 50, 52, 56 };
		int32 RandomMissionSelector = RandomMissionIndices[FMath::RandRange(0, 19)];

		// 랜덤 선택자에 따라서 bool[SUBMISSION_NUM] 타입인 bIsSubmissionDone를 초기화 및 할당
		for (int i = 0; i < 6; i++)
		{
			if (RandomMissionSelector % 2 == 1)
			{
				bIsSubmissionDone[i] = true;

				// UnsetSubMission(i)를 쓰지 않고 true 인자를 쓰는 로직을 사용
				// true 인자를 interactiontrigger로 넘기면 게임 시작 시에 발생하는 무결성 문제를 해결 가능
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

		// 메인 미션 관련 변수 초기화 (서브 미션은 InitializeMissions에서 처리)
		bIsMissionDone = false;
		MainMissionText = Arbiter->MAIN_MISSION_INIT;

		// 1초에 한 번씩 호출되는 타이머를 세팅. (초기값 5분)
		Time = 300;
		GetWorldTimerManager().SetTimer(MissionTickHandler, this, &AAstronautCharacter::MissionTick, 1.0f, true, 1.0f);
		
		MissionController->UpdateMainMissionDisplay();
		MissionController->UpdateSubMissionDisplay();

		// SignDisplay 설정
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
		// 월면 상공에 위치한 루나 게이트웨이 내부로 캐릭터 이동
		SetActorLocation({ -222951.0f, 31804.0f, 141102.0f });
		SetActorRotation({ 0.0f, 0.0f, 0.0f });

		Movement->GravityScale = 0.0f;
		RegisterHookHand();

		PullingForceDecrementCounter = 0;

		// 캐릭터 물리 체크 타이머 등록
		GetWorldTimerManager().SetTimer(ForceCheckHandler, this, &AAstronautCharacter::ForceChecker, 1.0f / 120, true, 1.0f / 120);
	}

	// Dialog Controller 활성화
	ADialogController* Dialog = Cast<ADialogController>(DialogController->GetChildActor());
	Dialog->SetActivated(true);
}

void AAstronautCharacter::OpenSelectMissionPanel()
{
	// TODO
}

void AAstronautCharacter::DoMainMission()
{
	bIsMissionDone = true;
	MainMissionText = Arbiter->MAIN_MISSION_DONE;

	Arbiter->MainStaticMeshControllable->SetStatus_Implementation(true);
	Arbiter->MainInteractionControllable->SetStatus_Implementation(false);
	Arbiter->MainGuideControllable->SetStatus_Implementation(false);

	// 미션 위젯 디스플레이 업데이트
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

	// 미션 위젯 디스플레이 업데이트
	MissionController->UpdateSubMissionDisplay();

	// 가이드 액터 Visibility 설정
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
		
	// 새로운 캐릭터 높이 사용
	GetCapsuleComponent()->SetCapsuleHalfHeight(EVACharacterHeight);
	FollowingCamera->SetRelativeLocation(FVector(30.0f, 0.0f, EVACharacterHeight + 3.0f));

	// 케이블 활성화
	Cable->SetHiddenInGame(false);

	// 캐릭터 위치 이동, 해당 위치에 케이블 연결
	SetActorLocation({ -223090.0, 31871.0, 141389.0 });
	SetActorRotation({ -EVACharacterPitch, 0.0f, 0.0f });
	RecentHookPoint = GetActorLocation();

	Movement->StopMovementImmediately();
	Movement->ClearAccumulatedForces();
}

void AAstronautCharacter::ReturnIVA()
{
	MoveType = EAstronautCSMMoveType::IVA;

	// 원래의 캐릭터 높이로 복귀
	GetCapsuleComponent()->SetCapsuleHalfHeight(80.0f);
	FollowingCamera->SetRelativeLocation(FVector(30.0f, 0.0f, 83.0f));

	// 케이블 비활성화
	Cable->SetHiddenInGame(true);

	// 캐릭터 위치 이동
	SetActorLocation({ -220307.0f, 31867.0f, 142149.0f });
	SetActorRotation({ 0.0f, -90.0f, 0.0f });

	// 케이블 길이 체크 타이머 해제
	// GetWorldTimerManager().ClearTimer(TimerHandler);

	Movement->StopMovementImmediately();
	Movement->ClearAccumulatedForces();
}

void AAstronautCharacter::OnGrip(AActor* HandActor, bool bIsLeft)
{
	// Sphere Tracing을 이용해 잡을 수 있는 스태틱 메시가 있는지 확인
	if (SelectedMission == EAstronautMissionType::CSM)
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
	if (SelectedMission == EAstronautMissionType::CSM)
	{
		// 선내 이동의 경우, Grip Point에서 밀어낸 위치에 비례해 반작용 힘을 받음
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
		// 선외 이동의 경우, 두 손을 다 떼는 순간 -y 방향으로 강한 힘을 받음
		else if (MoveType == EAstronautCSMMoveType::EVA)
		{
			if (bIsLeft && bIsGrabbingL)
			{
				bIsGrabbingL = false;
				if (!bIsGrabbingR)
				{
					Movement->AddForce(FVector(0.0f, -1.0f, 0.3f) * EVAExternalForceMagnitude);
					PullingForceDecrementCounter = 0;
				}
			}
			else if (!bIsLeft && bIsGrabbingR)
			{
				bIsGrabbingR = false;
				if (!bIsGrabbingL)
				{
					Movement->AddForce(FVector(0.0f, -1.0f, 0.3f) * EVAExternalForceMagnitude);
					PullingForceDecrementCounter = 0;
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

	// 안전줄을 연결할 부분을 찾은 경우 그 곳을 새로운 연결점으로 세팅
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

	// 허공에서 사용한 경우 안전줄의 시작 지점을 향해 힘을 받음
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
		// Cable의 End Location은 상대 위치로 결정되기 때문에 계속 업데이트 해주어야 함
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
// 멀티플레이 관련 함수 구현부입니다. //
// =============================== //

void AAstronautCharacter::OnRPCStartContent_Implementation()
{
	PlayInitialSequence();
}

void AAstronautCharacter::MakeRPCSelectMission_Implementation(int32 Mission)
{

}

void AAstronautCharacter::OnRPCCheckReadyState_Implementation()
{

}