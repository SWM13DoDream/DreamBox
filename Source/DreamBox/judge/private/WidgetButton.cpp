// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/WidgetButton.h"
#include "Components/WidgetComponent.h"

AWidgetButton::AWidgetButton()
{
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));

	RootComponent = DefaultSceneRoot;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Body->SetCollisionProfileName(TEXT("NoCollision"));
	Body->SetupAttachment(RootComponent);

	ButtonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BUTTON"));
	ButtonWidget->SetDrawSize(FVector2D(30.0f, 40.0f));
	ButtonWidget->SetRelativeRotation(FRotator(90.0f, 90.0f, 0.0f));
	ButtonWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ButtonWidget->SetupAttachment(RootComponent);

	NameWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("NAME_WIDGET"));
	NameWidget->SetDrawSize(FVector2D(300.f, 300.f));
	NameWidget->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	NameWidget->SetRelativeLocation(FVector(0.0f, -20.0f, 20.0f));
	NameWidget->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	NameWidget->SetCollisionProfileName(FName("NoCollision"));
	NameWidget->SetupAttachment(RootComponent);
}

void AWidgetButton::BeginPlay()
{
	Super::BeginPlay();
}
