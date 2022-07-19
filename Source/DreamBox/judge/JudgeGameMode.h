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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfActualJudgement);	// 실제 선고 시작 Delegate

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
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
		virtual void BeginPlay() override;

	// DataTable를 통해 Script와 Delay를 각각 배열에 집어넣는 함수
	UFUNCTION(BlueprintCallable)
		void AddArrayCPP(UDataTable* Table, TArray<FString> ScriptArray, TArray<float> DelayArray);

	UFUNCTION(BlueprintCallable)
		void TryStartOfCourtBattle();

	UFUNCTION(BlueprintCallable)
		void PetitionFunc();


public:

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfTrial StartOfTrial;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfCourtBattle StartOfCourtBattle;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfPetition StartOfPetition;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfFinalJudgement StartOfFinalJudgement;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfActualJudgement StartOfActualJudgement;

public:
	// 재판장 입장 나레이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NEnter;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NEnterScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NEnterDelay;

	// 안내 나레이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NGuide;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NGuideScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NGuideDelay;

	// 재판 시작 나레이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NTrialBegins;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NTrialBeginsScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NTrialBeginsDelay;

	// 법정공방 시작 나레이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NStartOfCourtBattle;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NStartOfCourtBattleScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NStartOfCourtBattleDelay;

	// 탄원서 시작 나레이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NStartOfPetition;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NStartOfPetitionScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NStartOfPetitionDelay;

	// 양형 나레이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NFinalJudgement;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NFinalJudgementScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NFinalJudgementDelay;

	// 실제 판결 나레이션
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NActualJudgement;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NActualJudgementScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NActualJudgementDelay;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "widgetActive")
		bool bWidgetIsActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Introduce")
		bool bOverview;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Introduce")
		bool bVideo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Introduce")
		bool bCondition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FinalOpinion")
		bool bPFinalOpinion;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FinalOpinion")
		bool bLFinalOpinion;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FinalOpinion")
		bool bDFinalOpinion;

};
