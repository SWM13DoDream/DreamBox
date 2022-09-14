// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/AstronautCharacter.h"
#include "../public/TimerWidget.h"
#include "../public/MissionWidget.h"
#include "../public/AstronautGamemode.h"
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
	IVAPullingForceDistanceThreshold = 80.0f;
	IVAPullingForceMultiplier = 3000.0f;
	IVAPushingForceMultiplier = 9000.0f;
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
	Gamemode->InitializeMission(this, SelectedMission);
}

// Called to bind functionality to input
void AAstronautCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAstronautCharacter::OnInteract);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AAstronautCharacter::ReleaseInteract);

	// 추가 입력 : 점프
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &ACharacter::StopJumping);

	// PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AAstronautCharacter::TryInteraction);
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
	if (SelectedMission == EAstronautMissionType::CSM
		&& MoveType == EAstronautCSMMoveType::IVA)
	{
		FVector TraceStartLocation = HandActor->GetActorLocation();
		FVector TraceEndLocation =
			TraceStartLocation + HandActor->GetActorForwardVector();
		TArray<TEnumAsByte<EObjectTypeQuery>> TargetTypes;
		TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
		TargetTypes.Add(WorldStatic);

		// Default parameters
		TArray<AActor*> IgnoreActors;
		FHitResult HitResult;

		bool bIsSphereTraceSucceed = UKismetSystemLibrary::SphereTraceSingleForObjects(
			GetWorld(), TraceStartLocation, TraceEndLocation, IVAGripRadius, TargetTypes,
			false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true
		);

		if (bIsSphereTraceSucceed)
		{
			Movement->StopMovementImmediately();

			UE_LOG(LogBlueprintUserMessages, Log, TEXT("Trace Succeed"));
			float Dist = UKismetMathLibrary::Vector_Distance(GetActorLocation(), TraceStartLocation);
			if (Dist > IVAPullingForceDistanceThreshold)
			{
				Movement->AddForce((TraceStartLocation - GetActorLocation()) * IVAPullingForceMultiplier);
			}

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
		else UE_LOG(LogBlueprintUserMessages, Log, TEXT("Trace Failed"));
	}
}

void AAstronautCharacter::ReleaseGrip(AActor* HandActor, bool bIsLeft)
{
	if (bIsLeft && bIsGrabbingL)
	{	
		FVector RelativeHandLocation = HandActor->GetActorLocation() - GetActorLocation();
		bIsGrabbingL = false;
		if (!bIsGrabbingR)
		{
			FVector Diff = RecentGrabbingPointL - RelativeHandLocation;
			Movement->AddForce(Diff * IVAPushingForceMultiplier);
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
		}
	}
}