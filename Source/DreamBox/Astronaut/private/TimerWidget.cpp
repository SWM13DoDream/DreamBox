// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/TimerWidget.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "TextFormatter"

UTimerWidget::UTimerWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TitleText")));
	ContentText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ContentText")));

	// �̸� ĳ���õ� �ֿ� ���� ������ ����
	Gamemode = Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

	// bIsAboardable ���� �ʱ� ���´� true
	bWasAboardable = true;
}

void UTimerWidget::UpdateDisplay()
{
	int32 Time = Gamemode->Time;

	// TitleText ���� ����
	if (Gamemode->IsAboardable() && Gamemode->bIsMissionDone)
	{
		TitleText->SetText(TITLE_DONEABLE);
	}
	else
	{
		TitleText->SetText(TITLE_NOT_DONEABLE);
	}

	// ContentText ���� ����
	FString SecString;
	SecString = SecString.Append("0").Append(FString::FromInt(Time % 60)).Right(2);
	
	FFormatNamedArguments Args;
	Args.Add(TEXT("Min"), Time / 60);
	Args.Add(TEXT("Sec"), FText::FromString(SecString));
	ContentText->SetText(FText::Format(LOCTEXT("Time", "{Min}:{Sec}"), Args));

	// ���� �����̼� ���� ȣ��
	ChangeTimerRotation((300 - Time) * 1.2f);

	// bWasAboardable ���� ������Ʈ
	if (bWasAboardable != Gamemode->IsAboardable())
	{
		bWasAboardable = Gamemode->IsAboardable();
		ChangeTimeColor(bWasAboardable);
	}
}