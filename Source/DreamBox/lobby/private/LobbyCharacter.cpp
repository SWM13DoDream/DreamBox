// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/LobbyCharacter.h"
#include "../../common/public/PersistentLevelBase.h"
#include "../public/LobbyGameModeBase.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

// Sets default values
ALobbyCharacter::ALobbyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called every frame
void ALobbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALobbyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Called when the game starts or when spawned
void ALobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitLevelScriptRef();
	InitLevelSequence();
	
	if (IsValid(LevelScriptRef))
	{
		LevelScriptRef->LoadingDoneEvent.AddDynamic(this, &ALobbyCharacter::PlayLobbyInitSequenceAnim);
	}
}

void ALobbyCharacter::InitLevelSequence()
{
	Super::InitLevelSequence();

	ALevelSequenceActor* OutActor = nullptr;
	if (IsValid(LobbyBeginAnimSequence))
	{
		LobbyBeginAnimSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LobbyBeginAnimSequence, FMovieSceneSequencePlaybackSettings(), OutActor);
	}
}

void ALobbyCharacter::PlayLobbyAppearAnim()
{
	if (IsValid(LobbyBeginAnimSequencePlayer))
	{
		LobbyBeginAnimSequencePlayer->Play();
	}
}

void ALobbyCharacter::InitLevelScriptRef()
{
	if (GetWorld())
	{
		LevelScriptRef = Cast<APersistentLevelBase>(GetWorld()->GetLevelScriptActor());
	}
}

void ALobbyCharacter::CallLevelLoadEndEvent()
{
	if (IsValid(LevelScriptRef))
	{
		LevelScriptRef->UnloadTransitionLevel();
	}
}
