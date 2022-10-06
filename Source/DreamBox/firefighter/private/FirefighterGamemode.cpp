// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/FirefighterGamemode.h"
#include "../public/FirefighterCharacter.h"
#include "../../common/public/PersistentLevelBase.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void AFirefighterGamemode::BeginPlay()
{
	Super::BeginPlay();

	//플레이어 캐릭터 레퍼런스 초기화 및 이벤트 바인딩
	if (GetWorld())
	{
		PlayerCharacterRef = Cast<AFirefighterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		PlayerCharacterRef->SetCharacterVisibility(false);
		if (IsValid(GetLevelScriptRef()))
		{
			GetLevelScriptRef()->PostLoadingDelegate.AddDynamic(this, &AFirefighterGamemode::PostLoadingEvent);
		}
	}
}

void AFirefighterGamemode::PostLoadingEvent()
{
	Super::PostLoadingEvent();

	PlayerCharacterRef->SetCharacterVisibility(true);
	PlayerCharacterRef->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	ShowInitialScript();
}

void AFirefighterGamemode::AddToCompleteSet(int32 MissionID)
{
	if (CompleteMissionSet.Contains(MissionID)) return;
	CompleteMissionSet.Add(MissionID);
}

bool AFirefighterGamemode::GetMissionIsComplete(int32 MissionID)
{
	return CompleteMissionSet.Contains(MissionID);
}

void AFirefighterGamemode::ShowInitialScript()
{
	if (!bShowInitScript) return;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
		ShowScriptWithID.Broadcast(0, InitialScriptID);
	}), 0.5f, false);
}