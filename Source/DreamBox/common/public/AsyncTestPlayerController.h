// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "AsyncTestPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DREAMBOX_API AAsyncTestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void AsyncLevelLoad(const FString& LevelDir, const FString& LevelName);

private:
	void AsyncLevelLoadFinished(const FString LevelName);
};
