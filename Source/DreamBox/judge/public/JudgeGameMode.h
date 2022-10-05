// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: AJudgeGameMode
- Description	: 모든 스크립트 DataTable 과 Delegate를 포함하고 있는 GameMode
- Date			: 2022-09-26 LJH
*/


#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/DreamBoxGameModeBase.h"
#include "Engine/DataTable.h"
#include "JudgeGameMode.generated.h"


// 재판 시작 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfTrial);

// 법정공방 시작 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfCourtBattle);

// 탄원서 시작 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfPetition);

// 선고 시작 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfFinalJudgement);

// 실제 선고 시작 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfActualJudgement);

// 데이터 테이블을 위한 사용자 지정 구조체 선언
USTRUCT(BlueprintType)
struct FScriptDT
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UDataTable* DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<float> Delay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;
};

/**
 *
 */
UCLASS()
class DREAMBOX_API AJudgeGameMode : public ADreamBoxGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void PreLoadingEndEvent() override;

	virtual void BeginPlay() override;

	// 로딩 직후의 BeginPlay
	virtual void PostLoadingEvent() override;	

	// DataTable을 기반으로 구조체에 데이터 Add
	UFUNCTION()
		void AddArray(FScriptDT& ScriptDT);
	

public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "EVENT")
		FStartOfTrial StartOfTrial;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "EVENT")
		FStartOfCourtBattle StartOfCourtBattle;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "EVENT")
		FStartOfPetition StartOfPetition;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "EVENT")
		FStartOfFinalJudgement StartOfFinalJudgement;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "EVENT")
		FStartOfActualJudgement StartOfActualJudgement;

	UFUNCTION(BlueprintCallable)
		bool TryStartOfCourtBattle();

	UFUNCTION(BlueprintCallable)
		bool TryStartOfPetition();

	UFUNCTION(BlueprintCallable)
		bool TryStartOfFinalJudgement();

	//BP의 Beginplay 로직을 AfterLoading이벤트로 옮기기 위한 게임 초기화 함수
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeGame();

public:
	// 위젯의 ON / OFF 여부를 위한 Boolean 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WIDGET_ACTIVE")
		bool bWidgetIsActive;

	// 한번의 Introduce 진행을 위한 Boolean 변수들
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "INTRODUCE")
		bool bDoOnceIntroduce = true;
	// 사건 개요 ( Case Overview )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "INTRODUCE")
		bool bOverview;
	// 사건 영상 ( Case Video )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "INTRODUCE")
		bool bVideo;
	// 양형 조건 ( Case Condition )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "INTRODUCE")
		bool bCondition;

	// 한번의 FinalOpinion을 위한 Boolean 변수들
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FINAL_OPINION")
		bool bDoOnceFinalOpinion = true;
	// 검사 최종의견 ( Prosecutor FinalOpinion )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FINAL_OPINION")
		bool bPFinalOpinion;
	// 변호사 최종의견 ( Lawyer FinalOpinion )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FINAL_OPINION")
		bool bLFinalOpinion;
	// 피고인 최종의견 ( Defendatn FinalOpinion )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FINAL_OPINION")
		bool bDFinalOpinion;

	// 한번의 Petition을 위한 Boolean 변수들
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PETITION")
		bool bDoOncePetition = true;
	// 피고인의 친구 탄원서
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PETITION")
		bool bFPetition;
	// 인근점포 상인 탄원서
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PETITION")
		bool bMPetition;

	// 각 진행상황에 따른 Script 저장
	// 입장 SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT Enter;
	// 안내 SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT Guide;
	// 재판 시작 SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT TrialBegins;
	// 법정공방 SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT CourtBattle;
	// 탄원서 SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT Petition;
	// 최종 판결 SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT FinalJudgement;
	// 실제 판결 SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT ActualJudgement;

	// 페이드 이펙트 ( Fade Effect )
	UFUNCTION(BlueprintCallable)
		void FadeIn();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FADE_EFFECT")
		class ULevelSequence* SQFadeIn;
	UFUNCTION(BlueprintCallable)
		void FadeOut();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FADE_EFFECT")
		class ULevelSequence* SQFadeOut;
	UFUNCTION(BlueprintCallable)
		void Fade();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FADE_EFFECT")
		class ULevelSequence* SQFade;
};