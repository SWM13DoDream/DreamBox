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

void AJudgeGameMode::AddArrayCPP(UDataTable* Table, TArray<FString> ScriptArray, TArray<float> DelayArray)
{
	TArray<FScriptStructure*> Array;
	Table->GetAllRows<FScriptStructure>(TEXT("GetAllRows"), Array);

	for (int i = 0; i < Array.Num(); ++i)
	{
		if (Array[i]->Script.Equals("")) break;
		ScriptArray.Add(*Array[i]->Script);
		DelayArray.Add(Array[i]->TimeLength);
	}
}

bool AJudgeGameMode::TryStartOfCourtBattle()
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), DoOnceIntroduce);
	UE_LOG(LogTemp, Warning, TEXT("%d"), bOverview);
	UE_LOG(LogTemp, Warning, TEXT("%d"), bVideo);
	UE_LOG(LogTemp, Warning, TEXT("%d"), bCondition);
	if (DoOnceIntroduce && (bOverview && bVideo && bCondition)) return true; // 법정공방 시작
	return false;
}

bool AJudgeGameMode::TryStartOfPetition()
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), DoOnceFinalOpinion);
	UE_LOG(LogTemp, Warning, TEXT("%d"), bPFinalOpinion);
	UE_LOG(LogTemp, Warning, TEXT("%d"), bLFinalOpinion);
	UE_LOG(LogTemp, Warning, TEXT("%d"), bDFinalOpinion);
	if (DoOnceFinalOpinion && (bPFinalOpinion && bLFinalOpinion && bDFinalOpinion)) return true; // 탄원서 시작
	else return false;
}

bool AJudgeGameMode::TryStartOfFinalJudgement()
{
	return DoOncePetition;
}
