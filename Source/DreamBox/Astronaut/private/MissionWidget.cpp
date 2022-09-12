// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/MissionWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../public/AstronautGamemode.h"

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

	// 미리 캐스팅된 주요 제어 변수를 저장
	Gamemode = Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
}