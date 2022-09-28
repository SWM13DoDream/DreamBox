// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: AJudgePlayerController
- Description	: 판사 캐릭터의 Character Controller를 담당
- Date			: 2022-07-11
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JudgePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DREAMBOX_API AJudgePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
