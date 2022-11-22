// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/JudgeGameMode.h"
#include "../public/SScriptStruct.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void AJudgeGameMode::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);
}

void AJudgeGameMode::PreLoadingEndEvent()
{
	Super::PreLoadingEndEvent();
	//InitializeGame();
}

void AJudgeGameMode::BeginPlay()
{
	Super::BeginPlay();

	AddArray(Enter);
	AddArray(Guide);
	AddArray(TrialBegins);
	AddArray(CourtBattle);
	AddArray(Petition);
	AddArray(FinalJudgement);
	AddArray(ActualJudgement);
}

void AJudgeGameMode::PostLoadingEvent()
{
	Super::PostLoadingEvent();
	InitializeGame();
}

void AJudgeGameMode::AddArray(FScriptDT& ScriptDT)
{
	TArray<FScriptStructure*> arr;

	ScriptDT.DataTable->GetAllRows<FScriptStructure>(TEXT("GetAllRows"), arr);

	for (int i = 0; i < arr.Num(); i++) {
		if (arr[i]->Script != "") {
			ScriptDT.Script.Add(arr[i]->Script);
			ScriptDT.Delay.Add(arr[i]->TimeLength);
		}
		else break;
	}
}

bool AJudgeGameMode::TryStartOfCourtBattle()
{
	if (bDoOnceIntroduce && (bOverview && bVideo && bCondition)) {
		bDoOnceIntroduce = false;
		return true; // 법정공방 시작
	}
	return false;
}

bool AJudgeGameMode::TryStartOfPetition()
{
	if (bDoOnceFinalOpinion && (bPFinalOpinion && bLFinalOpinion && bDFinalOpinion)) {
		bDoOnceFinalOpinion = false;
		return true; // 탄원서 시작
	}
	else return false;
}

bool AJudgeGameMode::TryStartOfFinalJudgement()
{
	if (bDoOncePetition && (bFPetition && bMPetition)) {
		bDoOncePetition = false;
		return true;
	}
	else return false;
}

void AJudgeGameMode::FadeIn()
{
	ALevelSequenceActor* OutActor = nullptr;
	
	ULevelSequencePlayer* CinematicSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SQFadeIn,
		FMovieSceneSequencePlaybackSettings(), OutActor);
	if (CinematicSequencePlayer)
	{
		CinematicSequencePlayer->Play();
		
	}
}

void AJudgeGameMode::FadeOut()
{
	ALevelSequenceActor* OutActor = nullptr;

	ULevelSequencePlayer* CinematicSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SQFadeOut,
		FMovieSceneSequencePlaybackSettings(), OutActor);
	if (CinematicSequencePlayer)
	{
		CinematicSequencePlayer->Play();

	}
}

void AJudgeGameMode::Fade()
{
	ALevelSequenceActor* OutActor = nullptr;

	ULevelSequencePlayer* CinematicSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SQFade,
		FMovieSceneSequencePlaybackSettings(), OutActor);
	if (CinematicSequencePlayer)
	{
		CinematicSequencePlayer->Play();

	}
}