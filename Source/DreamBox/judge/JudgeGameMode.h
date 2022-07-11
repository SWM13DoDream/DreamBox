// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: AJudgeGameMode
- Description	: 모든 스크립트 DataTable 과 Delegate를 포함하고 있는 GameMode
- Date			: 2022-07-11
*/


#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameMode.h"
#include "JudgeGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfTrial);			// 재판 시작 Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfCourtBattle);	// 법정공방 시작 Delegate 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfPetition);		// 탄원서 시작 Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfFinalJudgement);	// 선고 시작 Delegate

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

	// DataTable를 통해 Script와 Delay를 각각 배열에 집어넣는 함수
	UFUNCTION()
		void AddArray(UDataTable* Table, TArray<FString>& ScriptArray, TArray<float>& DelayArray);


public:

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfTrial StartOfTrial;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfCourtBattle StartOfCourtBattle;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfPetition StartOfPetition;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfFinalJudgement StartOfFinalJudgement;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NEnter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NGuide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NTrialBegins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NStartOfCourtBattle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NFinalJudgement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NActualJudgement;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		UDataTable* LMotive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		UDataTable* LDefendantThoughts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		UDataTable* LReimbursement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lawyer")
		UDataTable* LFinalOpinion;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		UDataTable* PCriminalBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		UDataTable* PCriminalRecord;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		UDataTable* PDegreeOfDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Prosecutor")
		UDataTable* PFinalOpinion;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dependant")
		UDataTable* DFinalOpinion;

public:

	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NEnterScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NEnterDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NGuideScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NGuideDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NTrialBeginsScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NTrialBeginsDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NStartOfCourtBattleScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NStartOfCourtBattleDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NFinalJudgementScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NFinalJudgementDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NActualJudgementScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NActualJudgementDelay;

public:

	UPROPERTY(BlueprintReadWrite, Category = "Lawyer")
		TArray<FString> LMotiveScript;
	UPROPERTY(BlueprintReadWrite, Category = "Lawyer")
		TArray<float> LMotiveDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Lawyer")
		TArray<FString> LDefendantThoughtsScript;
	UPROPERTY(BlueprintReadWrite, Category = "Lawyer")
		TArray<float>LDefendantThoughtsDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Lawyer")
		TArray<FString> LReimbursementScript;
	UPROPERTY(BlueprintReadWrite, Category = "Lawyer")
		TArray<float> LReimbursementDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Lawyer")
		TArray<FString> LFinalOpinionScript;
	UPROPERTY(BlueprintReadWrite, Category = "Lawyer")
		TArray<float> LFinalOpinionDelay;

public:

	UPROPERTY(BlueprintReadWrite, Category = "Prosecutor")
		TArray<FString> PCriminalBackgroundScript;
	UPROPERTY(BlueprintReadWrite, Category = "Prosecutor")
		TArray<float> PCriminalBackgroundDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Prosecutor")
		TArray<FString> PCriminalRecordScript;
	UPROPERTY(BlueprintReadWrite, Category = "Prosecutor")
		TArray<float> PCriminalRecordDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Prosecutor")
		TArray<FString> PDegreeOfDamageScript;
	UPROPERTY(BlueprintReadWrite, Category = "Prosecutor")
		TArray<float> PDegreeOfDamageDelay;


	UPROPERTY(BlueprintReadWrite, Category = "Prosecutor")
		TArray<FString> PFinalOpinionScript;
	UPROPERTY(BlueprintReadWrite, Category = "Prosecutor")
		TArray<float> PFinalOpinionDelay;

public:

	UPROPERTY(BlueprintReadWrite, Category = "Defendant")
		TArray<FString> DFinalOpinionScript;
	UPROPERTY(BlueprintReadWrite, Category = "Defendant")
		TArray<float> DFinalOpinionDelay;
};
