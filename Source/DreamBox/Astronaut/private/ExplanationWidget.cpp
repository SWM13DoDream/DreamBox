// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/ExplanationWidget.h"

UExplanationWidget::UExplanationWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UExplanationWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TitleText")));
	SubtitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("SubtitleText")));
	NavUpperTitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NavUpperTitleText")));
	NavUpperContentText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NavUpperContentText")));
	NavLowerTitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NavLowerTitleText")));
	NavLowerContentText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NavLowerContentText")));
	DescriptionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DescriptionText")));
}

void UExplanationWidget::SetIdentity(FExplanationStruct Value)
{
	Content = Value;

	TitleText->SetText(Value.Title);
	SubtitleText->SetText(Value.Subtitle);
	NavUpperTitleText->SetText(Value.NavUpperTitle);
	NavUpperContentText->SetText(Value.NavUpperContent);
	NavLowerTitleText->SetText(Value.NavLowerTitle);
	NavLowerContentText->SetText(Value.NavLowerContent);
	DescriptionText->SetText(Value.Description);

	SetImage(Value.Image);
}