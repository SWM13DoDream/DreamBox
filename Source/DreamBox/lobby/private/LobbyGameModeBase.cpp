// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/LobbyGameModeBase.h"
#include "../../common/public/PersistentLevelBase.h"

void ALobbyGameModeBase::BeginPlay()
{
	Super::BeginPlay(); 
	

}

void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);

	UE_LOG(LogTemp, Warning, TEXT("JOIN!----!"));

	
}

void ALobbyGameModeBase::PostLoadingEvent()
{
	Super::PostLoadingEvent();
}
