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
}

void ALobbyCharacter::InitLevelSequence()
{
	Super::InitLevelSequence();

}

void ALobbyCharacter::OnRPCStartContent(int32 PlayerID)
{
	//PlayLevelInitSequence();
}