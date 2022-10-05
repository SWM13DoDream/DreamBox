// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/InfoWidget.h"
#include "../public/AstronautCharacter.h"
#include "Kismet/GameplayStatics.h"

UInfoWidget::UInfoWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bActivated = false;

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player->IsLocallyControlled())
	{
		LocalPlayer = Cast<AAstronautCharacter>(Player);
	}
	else
	{
		Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);
		LocalPlayer = Cast<AAstronautCharacter>(Player);
	}
}