// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/SignWidget.h"

USignWidget::USignWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void USignWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TitleText")));
	SubtitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SubtitleText")));
	DescriptionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescriptionText")));
	StateText = Cast<UTextBlock>(GetWidgetFromName(TEXT("StateText")));
}

void USignWidget::SetIdentity(FSignStruct Value)
{
	Content = Value;
	TitleText->SetText(Value.Title);
	SubtitleText->SetText(Value.Subtitle);
	DescriptionText->SetText(Value.Description);
}