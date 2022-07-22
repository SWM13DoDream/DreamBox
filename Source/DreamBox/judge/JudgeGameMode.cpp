// Fill out your copyright notice in the Description page of Project Settings.


#include "./JudgeGameMode.h"


void AJudgeGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AJudgeGameMode::BeginPlay()
{
	Super::BeginPlay();
}

bool AJudgeGameMode::TryStartOfCourtBattle()
{
	if (bDoOnceIntroduce && (bOverview && bVideo && bCondition)) {
		bDoOnceIntroduce = false;
		return true; // �������� ����
	}
	return false;
}

bool AJudgeGameMode::TryStartOfPetition()
{
	if (bDoOnceFinalOpinion && (bPFinalOpinion && bLFinalOpinion && bDFinalOpinion)) {
		bDoOnceFinalOpinion = false;
		return true; // ź���� ����
	}
	else return false;
}

bool AJudgeGameMode::TryStartOfFinalJudgement()
{
	if (bDoOncePetition && (bFPetition && bMPetition)) {
		bDoOncePetition = false;
		return true;
	}
	else return false;
}
