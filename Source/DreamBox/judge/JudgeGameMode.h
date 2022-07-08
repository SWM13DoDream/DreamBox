// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameMode.h"
#include "JudgeGameMode.generated.h"

USTRUCT(BlueprintType)
struct FScriptStructure : public FTableRowBase
{
	GENERATED_BODY()

public:
	FScriptStructure() : Script(""), TimeLength(2.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float TimeLength;
};

/**
 *
 */
UCLASS()
class DREAMBOX_API AJudgeGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void BeginPlay() override;

	UFUNCTION()
	void AddArray(UDataTable* Table, TArray<FString>& ScriptArray, TArray<float>& DelayArray);

public:
	/* 나레이션 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* N_Enter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<FString> N_EnterScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<float> N_EnterDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* N_Guide;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<FString> N_GuideScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<float> N_GuideDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* N_TrialBegins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<FString> N_TrialBeginsScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<float> N_TrialBeginsDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* N_StartOfCourtBattle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<FString> N_StartOfCourtBattleScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<float> N_StartOfCourtBattleDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* N_FinalJudgement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<FString> N_FinalJudgementScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<float> N_FinalJudgementDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* N_ActualJudgement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<FString> N_ActualJudgementScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		TArray<float> N_ActualJudgementDelay;
	/* 나레이션 */

	/* 변호사 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		UDataTable* L_Motive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		TArray<FString> L_MotiveScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		TArray<float> L_MotiveDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		UDataTable* L_DefendantThoughts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		TArray<FString> L_DefendantThoughtsScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		TArray<float>L_DefendantThoughtsDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		UDataTable* L_Reimbursement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		TArray<FString> L_ReimbursementScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		TArray<float> L_ReimbursementDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		UDataTable* L_FinalOpinion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		TArray<FString> L_FinalOpinionScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		TArray<float> L_FinalOpinionDelay;
	/* 변호사 */

	/* 검사*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		UDataTable* P_CriminalBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		TArray<FString> P_CriminalBackgroundScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		TArray<float> P_CriminalBackgroundDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		UDataTable* P_CriminalRecord;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		TArray<FString> P_CriminalRecordScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		TArray<float> P_CriminalRecordDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		UDataTable* P_DegreeOfDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		TArray<FString> P_DegreeOfDamageScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		TArray<float> P_DegreeOfDamageDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		UDataTable* P_FinalOpinion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		TArray<FString> P_FinalOpinionScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		TArray<float> P_FinalOpinionDelay;
	/* 검사 */

	/* 피고인 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defendant")
		UDataTable* D_FinalOpinion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defendant")
		TArray<FString> D_FinalOpinionScript;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defendant")
		TArray<float> D_FinalOpinionDelay;
	/* 피고인 */
};
