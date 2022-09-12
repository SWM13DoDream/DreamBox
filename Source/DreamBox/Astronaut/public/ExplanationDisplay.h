// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautStructBase.h"
#include "ExplanationDisplay.generated.h"

/*
 - Name        : AExplanationDisplay
 - Description : 우주 비행사 컨텐츠의 설명 위젯을 관리하는 C++ 액터
 - Date        : 2022/09/01 DEVroar
*/

UCLASS()
class DREAMBOX_API AExplanationDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplanationDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// 전면 설명 위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* FrontWidgetComponent;

	// 후면 설명 위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* RearWidgetComponent;

public:
	UFUNCTION(BlueprintCallable)
		void SetExplanationContent(FExplanationStruct Value);
};
