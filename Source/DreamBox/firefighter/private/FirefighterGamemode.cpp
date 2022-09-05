// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/FirefighterGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "../public/FirefighterCharacter.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void AFirefighterGamemode::BeginPlay()
{
	Super::BeginPlay();

	InitLevelSequence();
	ShowInitialScript();
	
	//플레이어 캐릭터 레퍼런스 초기화
	if (GetWorld())
	{
		PlayerCharacterRef = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		CrossFadeAnimationEvent.AddDynamic(this, &AFirefighterGamemode::PlayCrossFadeAnim);
	}
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

void AFirefighterGamemode::InitLevelSequence()
{
	ALevelSequenceActor* OutActor = nullptr;
	CrossFadePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), CrossFade, FMovieSceneSequencePlaybackSettings(), OutActor);
}

void AFirefighterGamemode::ShowInitialScript()
{
	if (!bShowInitScript) return;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
		ShowScriptWithID.Broadcast(0, InitialScriptID);
	}), 0.5f, false);
}

void AFirefighterGamemode::PlayCrossFadeAnim(int32 PlayerID)
{
	if (!IsValid(CrossFadePlayer)) return;
	CrossFadePlayer->Play();
	
	if (IsValid(PlayerCharacterRef))
	{
		PlayerCharacterRef->GetCharacterMovement()->Deactivate();
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			PlayerCharacterRef->GetCharacterMovement()->Activate();
		}), 1.25f, false);
	}
}
