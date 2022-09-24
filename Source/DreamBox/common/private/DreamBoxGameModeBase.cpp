// Copyright Epic Games, Inc. All Rights Reserved.


#include "../public/DreamBoxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void ADreamBoxGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	InitLevelSequence();
}

void ADreamBoxGameModeBase::InitLevelSequence()
{
	ALevelSequenceActor* OutActor = nullptr;
	CrossFadePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), CrossFade, FMovieSceneSequencePlaybackSettings(), OutActor);
	LoadingEndEvent.AddDynamic(this, &ADreamBoxGameModeBase::BeginPlayAfterLoading);
}

void ADreamBoxGameModeBase::PlayCrossFadeAnim(int32 PlayerID)
{
	/* -- 플레이어 ID에 따라 구분할 로직이 들어갈 자리 -- */
	if (!IsValid(CrossFadePlayer)) return;
	CrossFadePlayer->Play();
}

void ADreamBoxGameModeBase::BeginPlayAfterLoading(int32 PlayerID)
{
	/* -- 플레이어 ID에 따라 구분할 로직이 들어갈 자리 -- */

}