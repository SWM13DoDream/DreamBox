// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/DialogWidget.h"

UDialogWidget::UDialogWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ContentText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ContentText")));
}

void UDialogWidget::SetIdentity(FText Value)
{
	Content = Value;
	ContentText->SetText(Content);
}