// Fill out your copyright notice in the Description page of Project Settings.


#include "./WidgetButton.h"

AWidgetButton::AWidgetButton()
{
	PrimaryActorTick.bCanEverTick = false;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	ButtonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BUTTON"));

	// Button 의 DrawSize 를 부착되는 Body의 크기에 맞게 작성
	ButtonWidget->SetDrawSize(FVector2D(17.0f, 20.0f));

}

void AWidgetButton::BeginPlay()
{
	Super::BeginPlay();
	
}