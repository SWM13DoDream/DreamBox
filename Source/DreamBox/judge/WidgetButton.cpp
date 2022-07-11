// Fill out your copyright notice in the Description page of Project Settings.


#include "./WidgetButton.h"

AWidgetButton::AWidgetButton()
{
	PrimaryActorTick.bCanEverTick = false;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	ButtonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BUTTON"));

	// Button �� DrawSize �� �����Ǵ� Body�� ũ�⿡ �°� �ۼ�
	ButtonWidget->SetDrawSize(FVector2D(17.0f, 20.0f));

}

void AWidgetButton::BeginPlay()
{
	Super::BeginPlay();
	
}