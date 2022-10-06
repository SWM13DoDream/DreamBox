// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/GamemodeArbiter.h"
#include "../public/AstronautCharacter.h"
#include "../public/AstronautGamemode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGamemodeArbiter::AGamemodeArbiter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGamemodeArbiter::BeginPlay()
{
	Super::BeginPlay();

	AAstronautCharacter* LocalPlayer;

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player->IsLocallyControlled())
	{
		LocalPlayer = Cast<AAstronautCharacter>(Player);
	}
	else
	{
		Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);
		LocalPlayer = Cast<AAstronautCharacter>(Player);
	}
	LocalPlayer->RegisterArbiter(this);
}

void AGamemodeArbiter::PostLoadingEvent()
{
	
	
}