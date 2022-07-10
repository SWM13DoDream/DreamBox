// Fill out your copyright notice in the Description page of Project Settings.


#include "./WidgetButton.h"

// Sets default values
AWidgetButton::AWidgetButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	RootComponent = Body;

	ButtonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BUTTON"));
	ButtonWidget->SetupAttachment(RootComponent);
	ButtonWidget->SetDrawSize(FVector2D(17.0f, 20.0f));

}

// Called when the game starts or when spawned
void AWidgetButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWidgetButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

