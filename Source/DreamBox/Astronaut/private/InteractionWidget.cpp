// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/InteractionWidget.h"
#include "../public/InteractionTrigger.h"


UInteractionWidget::UInteractionWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	IntroductionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("IntroductionText")));
	InteractionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("InteractionText")));
}

void UInteractionWidget::SetIdentity(class AInteractionTrigger* Parent, FInteractionStruct Value)
{
	Controller = Parent;
	Content = Value;

	IntroductionText->SetText(Content.Content);
	InteractionText->SetText(Content.Confirmation);
}

void UInteractionWidget::OnInteract()
{
	Controller->OnInteract();
}