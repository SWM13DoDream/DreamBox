// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: AJudgeGameMode
- Description	: 모든 스크립트 DataTable 과 Delegate를 포함하고 있는 GameMode
- Date			: 2022-08-12
- Version		: 1.0.1 Ver
*/


#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameMode.h"
#include "JudgeGameMode.generated.h"

// 데이터를 담기위한 구조체 생성
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

// 재판 시작 Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfTrial);
// 법정공방 시작 Delegate 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfCourtBattle);
// 탄원서 시작 Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfPetition);
// 선고 시작 Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfFinalJudgement);
// 실제 선고 시작 Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfActualJudgement);

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

public:
	// 법정 공방을 시작하기 전 사건 개요 / 사건 영상 / 양형 조건을 체크하기 위한 변수와 함수들
	UFUNCTION(BlueprintCallable)
		bool TryStartOfCourtBattle();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Introduce")
		bool bDoOnceIntroduce = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Introduce")
		bool bOverview;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Introduce")
		bool bVideo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Introduce")
		bool bCondition;

	// 탄원서를 시작하기 전 검사 / 변호사 / 피고인의 최종의견을 체크하기 위한 변수와 함수들
	UFUNCTION(BlueprintCallable)
		bool TryStartOfPetition();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FinalOpinion")
		bool bDoOnceFinalOpinion = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FinalOpinion")
		bool bPFinalOpinion;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FinalOpinion")
		bool bLFinalOpinion;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FinalOpinion")
		bool bDFinalOpinion;

	// 선고를 시작하기 전 피고인의 친구 / 인근 점포상인의 탄원서를 체크하기 위한 변수와 함수들
	UFUNCTION(BlueprintCallable)
		bool TryStartOfFinalJudgement();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Petition")
		bool bDoOncePetition = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Petition")
		bool bFPetition;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Petition")
		bool bMPetition;

	//위젯의 Active 여부를 체크하기 위한 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetActive")
		bool bWidgetIsActive;

public:
	// 입장 나레이션
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
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfTrial StartOfTrial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NTrialBegins;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NTrialBeginsScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NTrialBeginsDelay;

	// 법정공방 시작 나레이션
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfCourtBattle StartOfCourtBattle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NStartOfCourtBattle;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NStartOfCourtBattleScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NStartOfCourtBattleDelay;

	// 탄원서 시작 나레이션
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfPetition StartOfPetition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NStartOfPetition;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NStartOfPetitionScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NStartOfPetitionDelay;

	// 선고 나레이션
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfFinalJudgement StartOfFinalJudgement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NFinalJudgement;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NFinalJudgementScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NFinalJudgementDelay;

	// 실제 판결 나레이션
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfActualJudgement StartOfActualJudgement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NActualJudgement;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NActualJudgementScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NActualJudgementDelay;
};
