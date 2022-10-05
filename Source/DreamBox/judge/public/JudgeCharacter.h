// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../../common/public/DreamBox.h"
#include "JudgeCharacter.generated.h"

/*
- Name			: AJudgeCharacter
- Description	: �ǻ� ĳ���� WidgetIntercation�� ���� �ٸ� Widget ��� Interaction
- Date			: 2022-09-29 LJH
*/

UCLASS()
class DREAMBOX_API AJudgeCharacter : public AVRCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJudgeCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void PreLoadingEnd();
	
	UFUNCTION()
		void PostLoadingEvent();

public:
	//��ũ��Ʈ ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* ScriptWidget;
	
};
