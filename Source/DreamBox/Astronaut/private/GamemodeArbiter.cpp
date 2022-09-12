// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/GamemodeArbiter.h"
#include "Kismet/GameplayStatics.h"
#include "../public/AstronautGamemode.h"

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
	AAstronautGamemode* Gamemode = Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	Gamemode->RegisterArbiter(this);
}