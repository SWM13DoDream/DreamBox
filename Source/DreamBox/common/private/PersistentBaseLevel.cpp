// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/PersistentBaseLevel.h"
#include "../public/DreamBoxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void APersistentBaseLevel::BeginPlay()
{
	if (GetWorld())
	{
		GamemodeRef = Cast<ADreamBoxGameModeBase>(GetWorld()->GetAuthGameMode());
	}
	
	InitLevelSequencePlayer();
	SetupLevelOptions();
	LoadTargetLevelWithTransition();
}

void APersistentBaseLevel::SetupLevelOptions()
{
	FString OptionsString = GamemodeRef->OptionsString;

	if (OptionsString != "")
	{
		TransitionOptions.TargetLevelName = UGameplayStatics::ParseOption(OptionsString, "TargetLevelName");
		TransitionOptions.bPlayInitialAnimSequence = (UGameplayStatics::ParseOption(OptionsString, "bPlayInitialAnimSequence") == "true");
		TransitionOptions.bPlayFinalAnimSequence = (UGameplayStatics::ParseOption(OptionsString, "bPlayFinalAnimSequence") == "true");
	}
}

void APersistentBaseLevel::InitLevelSequencePlayer()
{
	ALevelSequenceActor* OutActor = nullptr;
	if (IsValid(AppearAnimSequence))
	{
		AppearAnimSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), AppearAnimSequence, FMovieSceneSequencePlaybackSettings(), OutActor);
	}
	if (IsValid(DisappearAnimSequence))
	{
		DisappearAnimSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), DisappearAnimSequence, FMovieSceneSequencePlaybackSettings(), OutActor);
	}
}

void APersistentBaseLevel::PlayAppearAnimSequence(bool bIsAppearAnim)
{
	if (bIsAppearAnim)
	{
		if (TransitionOptions.bPlayInitialAnimSequence && IsValid(AppearAnimSequencePlayer))
		{
			AppearAnimSequencePlayer->Play();
		}
	}
	else 
	{
		if (TransitionOptions.bPlayFinalAnimSequence && IsValid(DisappearAnimSequencePlayer))
		{
			DisappearAnimSequencePlayer->Play();
		}
	}
}