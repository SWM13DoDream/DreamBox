// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/ControllableStaticMesh.h"

// Sets default values
AControllableStaticMesh::AControllableStaticMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DEFAULT_MESH"));
	DefaultMesh->SetupAttachment(RootComponent);

	ActivatedMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ACTIVATED_MESH"));
	ActivatedMesh->SetupAttachment(RootComponent);

	bIsActivated = false;

	DefaultMesh->SetHiddenInGame(false);
	ActivatedMesh->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AControllableStaticMesh::BeginPlay()
{
	Super::BeginPlay();
}

void AControllableStaticMesh::SetActivation(bool Value)
{
	bIsActivated = Value;
	if (bIsActivated)
	{
		DefaultMesh->SetHiddenInGame(true);
		ActivatedMesh->SetHiddenInGame(false);

		OnActivated();
	}
}

void AControllableStaticMesh::SetStatus_Implementation(bool Value)
{
	SetActivation(Value);
}