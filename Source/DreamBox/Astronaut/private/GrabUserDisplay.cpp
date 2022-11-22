// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/GrabUserDisplay.h"
#include "Components/ArrowComponent.h"
#include "../public/AstronautCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGrabUserDisplay::AGrabUserDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EmptyComponent = CreateDefaultSubobject<USphereComponent>(TEXT("EMPTY_ROOT"));
	EmptyComponent->SetupAttachment(RootComponent);

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SPHERE_MESH"));
	SphereMesh->SetupAttachment(EmptyComponent);

	ForceArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FORCE_ARROW"));
	ForceArrow->SetupAttachment(EmptyComponent);
}

// Called when the game starts or when spawned
void AGrabUserDisplay::BeginPlay()
{
	Super::BeginPlay();
	SetActorHiddenInGame(true);
}

void AGrabUserDisplay::Initialize(AActor* Player, AActor* Hand, bool bIsLeft)
{
	PlayerActor = Cast<AAstronautCharacter>(Player);
	HandActor = Hand;
	bLeft = bIsLeft;
	SetActorRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ForceArrow->SetHiddenInGame(true);
}

void AGrabUserDisplay::ActivateDisplay(bool bEnableArrow)
{
	bEffectFlag = true;

	SphereMesh->SetRelativeScale3D(FVector(0.0f, 0.0f, 0.0f));
	SetActorHiddenInGame(false);
	ForceArrow->SetHiddenInGame(!bEnableArrow);
	LocationWhenActivated = GetActorLocation();
	GetWorldTimerManager().SetTimer(DisplayTickHandler, this, &AGrabUserDisplay::DisplayTick, 0.01f, true, 0.01f);
}

void AGrabUserDisplay::DisplayTick()
{
	if (bEffectFlag)
	{
		float SphereSize = SphereMesh->GetRelativeScale3D().X;
		SphereSize = SphereSize + 0.01f;

		if (SphereSize > 1.0f)
		{
			SphereSize = 0.0f;
			bEffectFlag = false;
		}

		SphereMesh->SetRelativeScale3D(FVector(SphereSize, SphereSize, SphereSize));
	}

	if (!ForceArrow->bHiddenInGame)
	{
		FVector SrcVector = GetActorLocation() - PlayerActor->GetActorLocation();
		FVector DstVector = (bLeft) ? PlayerActor->RecentGrabbingPointL : PlayerActor->RecentGrabbingPointR;

		float ArrowDistance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), LocationWhenActivated);
		FRotator ArrowRotation = UKismetMathLibrary::FindLookAtRotation(SrcVector, DstVector);
		ForceArrow->SetWorldRotation(ArrowRotation);
		// ForceArrow->ArrowLength = 20.0f + ArrowDistance;
		ForceArrow->ArrowLength = 50.0f;
	}
}

void AGrabUserDisplay::SetStatus_Implementation(bool Value)
{
	if (!Value)
	{
		SetActorHiddenInGame(true);
		GetWorldTimerManager().ClearTimer(DisplayTickHandler);
	}
}

AActor* AGrabUserDisplay::GetActor_Implementation()
{
	return this;
}