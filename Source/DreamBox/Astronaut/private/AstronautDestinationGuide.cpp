// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/AstronautDestinationGuide.h"

// Sets default values
AAstronautDestinationGuide::AAstronautDestinationGuide()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CylinderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CYLINDER_MESH"));
	CylinderMesh->SetupAttachment(RootComponent);

	ConeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CONE_MESH"));
	ConeMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAstronautDestinationGuide::BeginPlay()
{
	Super::BeginPlay();
}

void AAstronautDestinationGuide::SetVisibility(bool Value)
{
	CylinderMesh->SetVisibility(Value);
	ConeMesh->SetVisibility(Value);
}

void AAstronautDestinationGuide::SetStatus_Implementation(bool Value)
{
	SetVisibility(Value);
}