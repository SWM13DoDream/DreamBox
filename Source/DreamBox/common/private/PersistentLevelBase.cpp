// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/PersistentLevelBase.h"
#include "../public/DreamBoxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void APersistentLevelBase::BeginPlay()
{
	if (GetWorld())
	{
		GamemodeRef = Cast<ADreamBoxGameModeBase>(GetWorld()->GetAuthGameMode());
		if (IsValid(GamemodeRef))
		{
			SetupLevelOptions();
			GamemodeRef->InitLevelScriptRef(this);
			LoadTargetLevel();
		}
	}
}

void APersistentLevelBase::SetupLevelOptions()
{
	if (!IsValid(GamemodeRef)) return;

	FString OptionsString = GamemodeRef->OptionsString;
	if (OptionsString != FString(""))
	{
		TransitionOptions.TargetLevelName = UGameplayStatics::ParseOption(OptionsString, "TargetLevelName");
		TransitionOptions.bPlayInitialAnimSequence = (UGameplayStatics::ParseOption(OptionsString, "bPlayInitialAnimSequence") == "true");
		TransitionOptions.bPlayFinalAnimSequence = (UGameplayStatics::ParseOption(OptionsString, "bPlayFinalAnimSequence") == "true");
	}
}


void APersistentLevelBase::BroadcastPostLoadingEvent()
{
	PostLoadingDelegate.Broadcast();
}
