// Fill out your copyright notice in the Description page of Project Settings.


#include "./Introduce.h"

// Sets default values
AIntroduce::AIntroduce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGET"));
	Widget->SetDrawSize(FVector2D(1920.f, 1080.f));

	RootComponent = Widget;
}

// Called when the game starts or when spawned
void AIntroduce::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIntroduce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

