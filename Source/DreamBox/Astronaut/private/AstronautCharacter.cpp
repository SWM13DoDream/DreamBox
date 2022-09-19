// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/AstronautCharacter.h"
#include "../public/TimerWidget.h"
#include "../public/MissionWidget.h"
#include "../public/AstronautGamemode.h"
#include "../../../../../Plugins/Runtime/CableComponent/Source/CableComponent/Classes/CableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAstronautCharacter::AAstronautCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->Tags = { "Player" };

	TimerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TIMER_WIDGET"));
	TimerWidget->SetupAttachment(VROrigin);

	MissionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MISSION_WIDGET"));
	MissionWidget->SetupAttachment(VROrigin);

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

	AAstronautGamemode* Gamemode = Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	Gamemode->RegisterWidgetControllers(
		Cast<UTimerWidget>(TimerWidget->GetWidget()),
		Cast<UMissionWidget>(MissionWidget->GetWidget())
	);

	Movement = this->GetCharacterMovement();

	// TEST: 현재 사령선 임무 관련 테스트 중
	InitializeMission();
	Gamemode->InitializeMission(this, SelectedMission);
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

void AAstronautCharacter::InitializeMission()
{
	if (SelectedMission == EAstronautMissionType::LEM)
	{
		// 월면 기지에 위치한 탐사선 내부로 캐릭터 이동
		SetActorLocation({ -22009.0f, -25467.0f, -106513.0f });
		SetActorRotation({ 0.0f, 80.0f, 0.0f });

		Movement->GravityScale = 0.17f;
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
		GetWorldTimerManager().SetTimer(TimerHandler, this, &AAstronautCharacter::ForceChecker, 1.0f / 120, true, 1.0f / 120);
	}
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

void AAstronautCharacter::OnInteract()
{
	WidgetInteraction->PressPointerKey(EKeys::LeftMouseButton);
}

void AAstronautCharacter::ReleaseInteract()
{
	WidgetInteraction->ReleasePointerKey(EKeys::LeftMouseButton);
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
				for (FHitResult Target : HitResults)
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
		for (FHitResult Target : HitResults)
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