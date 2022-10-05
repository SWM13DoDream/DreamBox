// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/MissionSelectionPanel.h"
#include "../public/AstronautCharacter.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMissionSelectionPanel::AMissionSelectionPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EmptyComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ROOT_EMPTY"));
	EmptyComponent->SetupAttachment(RootComponent);

	MainWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MAIN_WIDGET"));
	MainWidget->SetupAttachment(EmptyComponent);

	WaitingWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WAITING_WIDGET"));
	WaitingWidget->SetupAttachment(EmptyComponent);
}

// Called when the game starts or when spawned
void AMissionSelectionPanel::BeginPlay()
{
	Super::BeginPlay();
	
	MainWidget->SetHiddenInGame(true);
	WaitingWidget->SetHiddenInGame(true);
}

void AMissionSelectionPanel::SetStatus_Implementation(bool Value)
{
	if (!Value) Activate();
	else Deactivate();
}

AActor* AMissionSelectionPanel::GetActor_Implementation()
{
	return this;
}

void AMissionSelectionPanel::SelectMission(int32 Mission)
{
	GetLocalPlayer()->SelectMission(Mission);
}

class AAstronautCharacter* AMissionSelectionPanel::GetLocalPlayer()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player->IsLocallyControlled()) return Cast<AAstronautCharacter>(Player);
	else
	{
		Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);
		return Cast<AAstronautCharacter>(Player);
	}
}