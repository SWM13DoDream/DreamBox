// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: AJudgeGameMode
- Description	: ��� ��ũ��Ʈ DataTable �� Delegate�� �����ϰ� �ִ� GameMode
- Date			: 2022-07-11
*/


#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameMode.h"
#include "JudgeGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfTrial);				// ���� ���� Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfCourtBattle);		// �������� ���� Delegate 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfPetition);			// ź���� ���� Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfFinalJudgement);		// ���� ���� Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfActualJudgement);	// ���� ���� ���� Delegate

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

	UFUNCTION(BlueprintCallable)
		bool TryStartOfCourtBattle();

	UFUNCTION(BlueprintCallable)
		bool TryStartOfPetition();

	UFUNCTION(BlueprintCallable)
		bool TryStartOfFinalJudgement();


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
	// ������ ���� �����̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NEnter;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NEnterScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NEnterDelay;

	// �ȳ� �����̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NGuide;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NGuideScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NGuideDelay;

	// ���� ���� �����̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NTrialBegins;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NTrialBeginsScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NTrialBeginsDelay;

	// �������� ���� �����̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NStartOfCourtBattle;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NStartOfCourtBattleScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NStartOfCourtBattleDelay;

	// ź���� ���� �����̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NStartOfPetition;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NStartOfPetitionScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NStartOfPetitionDelay;

	// ���� �����̼�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NFinalJudgement;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NFinalJudgementScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NFinalJudgementDelay;

	// ���� �ǰ� �����̼�
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


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Petition")
		bool bFPetition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Petition")
		bool bMPetition;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Introduce")
		bool bDoOnceIntroduce = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FinalOpinion")
		bool bDoOnceFinalOpinion = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Petition")
		bool bDoOncePetition = true;

};
