// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/Introduce.h"
#include "../public/JudgeGameMode.h"
#include "Components/WidgetComponent.h"

// Sets default values
AIntroduce::AIntroduce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = SceneComponent;

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGET"));
	Widget->SetDrawSize(FVector2D(1920.f, 1080.f));
	Widget->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f));
	Widget->SetupAttachment(RootComponent);

	NextPage = CreateDefaultSubobject<UWidgetComponent>(TEXT("NextPage"));
	NextPage->SetDrawSize(FVector2D(1300.f, 100.f));
	NextPage->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
	NextPage->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	NextPage->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AIntroduce::BeginPlay()
{
	Super::BeginPlay();

	if (isNextPage) NextPage->SetHiddenInGame(false);
	else NextPage->SetHiddenInGame(true);
}

// Called every frame
void AIntroduce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

