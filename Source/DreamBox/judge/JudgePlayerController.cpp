// Fill out your copyright notice in the Description page of Project Settings.


#include "./JudgePlayerController.h"

void AJudgePlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
