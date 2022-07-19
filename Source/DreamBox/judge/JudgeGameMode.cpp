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

void AJudgeGameMode::TryStartOfCourtBattle()
{
	if (bOverview && bVideo && bCondition) StartOfCourtBattle.Broadcast();
}

void AJudgeGameMode::PetitionFunc()
{
	if (bPFinalOpinion && bLFinalOpinion && bDFinalOpinion) StartOfPetition.Broadcast();
}
