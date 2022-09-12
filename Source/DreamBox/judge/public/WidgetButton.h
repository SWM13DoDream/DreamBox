// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: AWidgetButton
- Description	: 각 3D Floating Widget을 생성하기 위한 Button Actor
- Date			: 2022-09-06
*/

#pragma once

#include "../../common/public/DreamBox.h"
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

	UPROPERTY(VisibleAnywhere, Category = "ROOT")
		USceneComponent* DefaultSceneRoot;

	// BODY를 위한 StaticMeshComponent
	UPROPERTY(VisibleAnywhere, Category = "BODY")
		UStaticMeshComponent* Body;

	// NameWidget을 위한 Name 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NAME")
		FText Name;

	// 3D Float Widget 생성 버튼 위한 ButtonWidget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BUTTON")
		class UWidgetComponent* ButtonWidget;

	// Widget의 설명을 위한 NameWiget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NAME_WIDGET")
		class UWidgetComponent* NameWidget;
};
