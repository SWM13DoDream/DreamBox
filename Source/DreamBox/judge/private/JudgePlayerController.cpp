// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/JudgePlayerController.h"
#include "../public/JudgeGameMode.h"

void AJudgePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// GameMode�� InputMode�� ���������ν� ���� ���� �� ����Ʈ Ŭ�� ���� �ذ�
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

