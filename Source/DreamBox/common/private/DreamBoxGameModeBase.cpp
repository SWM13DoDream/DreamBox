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
	/* -- �÷��̾� ID�� ���� ������ ������ �� �ڸ� -- */
	if (!IsValid(CrossFadePlayer)) return;
	CrossFadePlayer->Play();
}

void ADreamBoxGameModeBase::BeginPlayAfterLoading(int32 PlayerID)
{
	/* -- �÷��̾� ID�� ���� ������ ������ �� �ڸ� -- */

}