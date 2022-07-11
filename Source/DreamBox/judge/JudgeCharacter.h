// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetInteractionComponent.h"

#include "JudgeCharacter.generated.h"

/*
- Name			: AJudgeCharacter
- Description	: 판사 캐릭터 WidgetIntercation을 통해 다른 Widget 들과 Interaction 함
- Date			: 2022-07-11
*/


UCLASS()
class DREAMBOX_API AJudgeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJudgeCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "WidgetInteraction")
		UWidgetInteractionComponent* WidgetInteraction;



private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);

	void Turn(float NewAxisValue);
	void LookUp(float NewAxisValue);

	void LClickPressed();
	void LClickReleased();
};
