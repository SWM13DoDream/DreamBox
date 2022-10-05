// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/MissionWidget.h"
#include "../public/AstronautCharacter.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "TextFormatter"

UMissionWidget::UMissionWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UMissionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MainContentText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MainContentText")));
	SubContentText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SubContentList")));

	// �̸� ĳ���õ� �ֿ� ���� ������ ����
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player->IsLocallyControlled()) LocalPlayer = Cast<AAstronautCharacter>(Player);
	else
	{
		Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);
		LocalPlayer = Cast<AAstronautCharacter>(Player);
	}
}