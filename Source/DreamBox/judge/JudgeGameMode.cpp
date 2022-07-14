// Fill out your copyright notice in the Description page of Project Settings.


#include "./JudgeGameMode.h"

void AJudgeGameMode::BeginPlay()
{
	AddArray(NEnter, NEnterScript, NEnterDelay);
	AddArray(NGuide, NGuideScript, NGuideDelay);
	AddArray(NTrialBegins, NTrialBeginsScript, NTrialBeginsDelay);
	AddArray(NStartOfCourtBattle, NStartOfCourtBattleScript, NStartOfCourtBattleDelay);
	AddArray(NFinalJudgement, NFinalJudgementScript, NFinalJudgementDelay);
	AddArray(NActualJudgement, NActualJudgementScript, NActualJudgementDelay);
}

void AJudgeGameMode::AddArray(UDataTable* Table, TArray<FString>& ScriptArray, TArray<float>& DelayArray)
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
