// Fill out your copyright notice in the Description page of Project Settings.


#include "./WidgetButton.h"
#include "./JudgeGameMode.h"

AWidgetButton::AWidgetButton()
{
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	ButtonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BUTTON"));

	RootComponent = DefaultSceneRoot;
	
	Body->SetCollisionProfileName(TEXT("NoCollision"));

	// Button 의 DrawSize 를 부착되는 Body의 크기에 맞게 작성
	ButtonWidget->SetDrawSize(FVector2D(29.0f, 37.0f));
	ButtonWidget->SetRelativeRotation(FRotator(90.0f,0.0f,0.0f));
	
	Body->SetupAttachment(RootComponent);
	ButtonWidget->SetupAttachment(RootComponent);
}

void AWidgetButton::BeginPlay()
{
	Super::BeginPlay();
}
