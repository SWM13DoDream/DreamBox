// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/WidgetComponent.h"
#include "JudgeCharacter.generated.h"

/*
- Name			: AJudgeCharacter
- Description	: 판사 캐릭터 WidgetIntercation을 통해 다른 Widget 들과 Interaction
- Date			: 2022-08-12
- Version		: 1.0.1 Ver
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
	// 캐릭터의 Script를 보여주기 위한 위한 ScriptWidget
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ScriptWidget")
	//	UWidgetComponent* ScriptWidget;

private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
};
