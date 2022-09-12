// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/JudgePlayerController.h"

void AJudgePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// GameMode로 InputMode를 설정함으로써 게임 시작 후 뷰포트 클릭 문제 해결
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
