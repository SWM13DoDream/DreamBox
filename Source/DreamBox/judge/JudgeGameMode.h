// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: AJudgeGameMode
- Description	: ��� ��ũ��Ʈ DataTable �� Delegate�� �����ϰ� �ִ� GameMode
- Date			: 2022-08-12
- Version		: 1.0.1 Ver
*/


#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameMode.h"
#include "JudgeGameMode.generated.h"

// �����͸� ������� ����ü ����
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

// ���� ���� Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfTrial);
// �������� ���� Delegate 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfCourtBattle);
// ź���� ���� Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfPetition);
// ���� ���� Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfFinalJudgement);
// ���� ���� ���� Delegate
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
	// ���� ������ �����ϱ� �� ��� ���� / ��� ���� / ���� ������ üũ�ϱ� ���� ������ �Լ���
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

	// ź������ �����ϱ� �� �˻� / ��ȣ�� / �ǰ����� �����ǰ��� üũ�ϱ� ���� ������ �Լ���
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

	// ���� �����ϱ� �� �ǰ����� ģ�� / �α� ���������� ź������ üũ�ϱ� ���� ������ �Լ���
	UFUNCTION(BlueprintCallable)
		bool TryStartOfFinalJudgement();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Petition")
		bool bDoOncePetition = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Petition")
		bool bFPetition;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Petition")
		bool bMPetition;

	//������ Active ���θ� üũ�ϱ� ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WidgetActive")
		bool bWidgetIsActive;

public:
	// ���� �����̼�
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
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfTrial StartOfTrial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NTrialBegins;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NTrialBeginsScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NTrialBeginsDelay;

	// �������� ���� �����̼�
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfCourtBattle StartOfCourtBattle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NStartOfCourtBattle;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NStartOfCourtBattleScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NStartOfCourtBattleDelay;

	// ź���� ���� �����̼�
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfPetition StartOfPetition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NStartOfPetition;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NStartOfPetitionScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NStartOfPetitionDelay;

	// ���� �����̼�
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfFinalJudgement StartOfFinalJudgement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NFinalJudgement;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NFinalJudgementScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NFinalJudgementDelay;

	// ���� �ǰ� �����̼�
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
		FStartOfActualJudgement StartOfActualJudgement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Narration")
		UDataTable* NActualJudgement;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<FString> NActualJudgementScript;
	UPROPERTY(BlueprintReadWrite, Category = "Narration")
		TArray<float> NActualJudgementDelay;
};
