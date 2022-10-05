// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: AJudgeGameMode
- Description	: ��� ��ũ��Ʈ DataTable �� Delegate�� �����ϰ� �ִ� GameMode
- Date			: 2022-09-26 LJH
*/


#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/DreamBoxGameModeBase.h"
#include "Engine/DataTable.h"
#include "JudgeGameMode.generated.h"


// ���� ���� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfTrial);

// �������� ���� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfCourtBattle);

// ź���� ���� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfPetition);

// ���� ���� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfFinalJudgement);

// ���� ���� ���� ��������Ʈ
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartOfActualJudgement);

// ������ ���̺��� ���� ����� ���� ����ü ����
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

	// �ε� ������ BeginPlay
	virtual void PostLoadingEvent() override;	

	// DataTable�� ������� ����ü�� ������ Add
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

	//BP�� Beginplay ������ AfterLoading�̺�Ʈ�� �ű�� ���� ���� �ʱ�ȭ �Լ�
	UFUNCTION(BlueprintImplementableEvent)
		void InitializeGame();

public:
	// ������ ON / OFF ���θ� ���� Boolean ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WIDGET_ACTIVE")
		bool bWidgetIsActive;

	// �ѹ��� Introduce ������ ���� Boolean ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "INTRODUCE")
		bool bDoOnceIntroduce = true;
	// ��� ���� ( Case Overview )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "INTRODUCE")
		bool bOverview;
	// ��� ���� ( Case Video )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "INTRODUCE")
		bool bVideo;
	// ���� ���� ( Case Condition )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "INTRODUCE")
		bool bCondition;

	// �ѹ��� FinalOpinion�� ���� Boolean ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FINAL_OPINION")
		bool bDoOnceFinalOpinion = true;
	// �˻� �����ǰ� ( Prosecutor FinalOpinion )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FINAL_OPINION")
		bool bPFinalOpinion;
	// ��ȣ�� �����ǰ� ( Lawyer FinalOpinion )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FINAL_OPINION")
		bool bLFinalOpinion;
	// �ǰ��� �����ǰ� ( Defendatn FinalOpinion )
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "FINAL_OPINION")
		bool bDFinalOpinion;

	// �ѹ��� Petition�� ���� Boolean ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PETITION")
		bool bDoOncePetition = true;
	// �ǰ����� ģ�� ź����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PETITION")
		bool bFPetition;
	// �α����� ���� ź����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PETITION")
		bool bMPetition;

	// �� �����Ȳ�� ���� Script ����
	// ���� SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT Enter;
	// �ȳ� SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT Guide;
	// ���� ���� SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT TrialBegins;
	// �������� SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT CourtBattle;
	// ź���� SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT Petition;
	// ���� �ǰ� SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT FinalJudgement;
	// ���� �ǰ� SCRIPT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NARRATION")
		FScriptDT ActualJudgement;

	// ���̵� ����Ʈ ( Fade Effect )
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