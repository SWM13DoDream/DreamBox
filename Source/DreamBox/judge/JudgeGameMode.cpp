// Fill out your copyright notice in the Description page of Project Settings.


#include "./JudgeGameMode.h"

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

void AJudgeGameMode::BeginPlay()
{
	AddArray(N_Enter, N_EnterScript, N_EnterDelay);
	AddArray(N_Guide, N_GuideScript, N_GuideDelay);
	AddArray(N_TrialBegins, N_TrialBeginsScript, N_TrialBeginsDelay);
	AddArray(N_StartOfCourtBattle, N_StartOfCourtBattleScript, N_StartOfCourtBattleDelay);
	AddArray(N_FinalJudgement, N_FinalJudgementScript, N_FinalJudgementDelay);
	AddArray(N_ActualJudgement, N_ActualJudgementScript, N_ActualJudgementDelay);
	

	AddArray(L_Motive, L_MotiveScript, L_MotiveDelay);
	AddArray(L_DefendantThoughts, L_DefendantThoughtsScript, L_DefendantThoughtsDelay);
	AddArray(L_Reimbursement, L_ReimbursementScript, L_ReimbursementDelay);
	AddArray(L_FinalOpinion, L_FinalOpinionScript, L_FinalOpinionDelay);

	AddArray(P_CriminalBackground, P_CriminalBackgroundScript, P_CriminalBackgroundDelay);
	AddArray(P_CriminalRecord, P_CriminalRecordScript, P_CriminalRecordDelay);
	AddArray(P_DegreeOfDamage, P_DegreeOfDamageScript, P_DegreeOfDamageDelay);
	AddArray(P_FinalOpinion, P_FinalOpinionScript, P_FinalOpinionDelay);

	AddArray(D_FinalOpinion, D_FinalOpinionScript, D_FinalOpinionDelay);
}
