// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/FirefighterGamemode.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void AFirefighterGamemode::BeginPlay()
{
	Super::BeginPlay();

	InitLevelSequence();
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

void AFirefighterGamemode::InitLevelSequence()
{
	ALevelSequenceActor* OutActor = nullptr;
	CrossFadePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), CrossFade, FMovieSceneSequencePlaybackSettings(), OutActor);
}

void AFirefighterGamemode::ShowInitialScript()
{
	float WaitTime = 0.5f;
	if (!bShowInitScript) return;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
		ShowScriptWithID.Broadcast(0, InitialScriptID);
	}), WaitTime, false);
}

void AFirefighterGamemode::PlayCrossFadeAnim(int32 PlayerID)
{
	if (!IsValid(CrossFadePlayer)) return;
	CrossFadePlayer->Play();
}
