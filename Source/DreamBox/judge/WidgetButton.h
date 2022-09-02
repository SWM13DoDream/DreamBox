// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: AWidgetButton
- Description	: 각 3D Floating Widget을 생성하기 위한 Button Actor
- Date			: 2022-07-11
*/

#pragma once

#include "EngineMinimal.h"
#include "./JudgeGameMode.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "WidgetButton.generated.h"


UCLASS()
class DREAMBOX_API AWidgetButton : public AActor
{
	GENERATED_BODY()

public:
	AWidgetButton();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, Category = "Root")
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Body")
		UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
		UWidgetComponent* ButtonWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
		UWidgetComponent* NameWidget;
};
