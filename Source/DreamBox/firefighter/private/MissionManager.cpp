// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/MissionManager.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMissionManager::AMissionManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	MissionListWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MISSION_WIDGET"));
	MissionListWidget->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AMissionManager::BeginPlay()
{
	Super::BeginPlay();
	MissionListWidgetRef = Cast<UUserWidget>(MissionListWidget->GetWidget());
}

void AMissionManager::UpdateMissionWidgetEvent(int32 MissionID, int32 Variable)
{
	if (Variable == 0) AddNewMission(MissionID); //미션 갱신값이 0이라면? 새로운 미션
	else UpdateMission(MissionID, Variable); //그게 아니라면 그만큼 업데이트
}

void AMissionManager::RemoveMission(int32 TargetMissionID)
{
	UpdateMission(TargetMissionID, 2e9); //강제로 미션을 완료시킨다.
}
