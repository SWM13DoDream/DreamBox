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

	SelectedMission = EAstronautMissionType::LEM;
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

	// Gamemode->InitializeMission(this, SelectedMission);

	// TEST: 현재 사령선 임무 관련 테스트 중
	Gamemode->InitializeMission(this, EAstronautMissionType::CSM);
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