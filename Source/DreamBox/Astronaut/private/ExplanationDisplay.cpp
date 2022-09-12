// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/ExplanationDisplay.h"
#include "Components/WidgetComponent.h"
#include "../public/ExplanationWidget.h"

// Sets default values
AExplanationDisplay::AExplanationDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FrontWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("FRONT_WIDGET"));
	FrontWidgetComponent->SetupAttachment(RootComponent);

	RearWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("REAR_WIDGET"));
	RearWidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AExplanationDisplay::BeginPlay()
{
	Super::BeginPlay();	
}

void AExplanationDisplay::SetExplanationContent(FExplanationStruct Value)
{
	UExplanationWidget* FrontWidget = Cast<UExplanationWidget>(FrontWidgetComponent->GetWidget());
	FrontWidget->SetIdentity(Value);

	UExplanationWidget* RearWidget = Cast<UExplanationWidget>(RearWidgetComponent->GetWidget());
	RearWidget->SetIdentity(Value);
}
