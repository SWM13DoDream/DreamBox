// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautStructBase.h"
#include "ExplanationDisplay.generated.h"

/*
 - Name        : AExplanationDisplay
 - Description : ���� ����� �������� ���� ������ �����ϴ� C++ ����
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
	// ���� ���� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* FrontWidgetComponent;

	// �ĸ� ���� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* RearWidgetComponent;

public:
	UFUNCTION(BlueprintCallable)
		void SetExplanationContent(FExplanationStruct Value);
};
