// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "GameFramework/GameModeBase.h"
#include "AstronautGamemode.generated.h"

/*
 - Name        : AAstronautGamemode
 - Description : ���ֺ���� ���� ���Ӹ��
 - Date        : 2022/07/26 DEVroar
*/

// ���ֺ������ �ӹ� ����� ENUM���� ����
UENUM(BlueprintType)
namespace EAstronautMissionType
{
	enum Type
	{
		/** Ž�缱 �ӹ� - ���� �������� ���� */
		LEM,

		/** ��ɼ� �ӹ� - �糪 ����Ʈ���̿��� ���� */
		CSM
	};
}

UCLASS()
class DREAMBOX_API AAstronautGamemode : public AGameModeBase
{
	GENERATED_BODY()

private:
	// ��ɼ� ���� �ֱ� �����
	const int32 TIME_PERIOD = 300;

	// ���� �ӹ� ���� �����
	const int32 SUBMISSION_NUM = 6;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 1�ʸ��� ����Ǵ� Ÿ�̸� �ڵ鷯
	void HandleTimer();
	FTimerHandle TimerHandler;

	// �̼� ���� ǥ�� TEXT �����. �Ļ� BP���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText MAIN_MISSION_INIT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText MAIN_MISSION_DONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		TArray<FText> SUB_MISSION_TEXT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText SUB_MISSION_DONE;

public:
	// ĳ���� Ÿ�̸� ���� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		UTimerWidget* CharacterTimerController;

	// ĳ���� �̼� ���� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		UMissionWidget* CharacterMissionController;

	// ���Ӹ�� ����Ʈ �߰� ���� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		AGamemodeArbiter* Arbiter;

public:
	// ���� �̼��� �����ϰ� ������ �ִ� ���͸� �����Ͽ� ������ �����ϴ� �Լ�
	// ���Ἲ�� ���� BeginPlay ȣ�� �ð� �ƴ϶� Arbiter ��� �ÿ� ȣ���
	UFUNCTION(BlueprintCallable)
		void InitializeMissions();

	// ���� �̼��� Ȱ��ȭ �� �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
		void ConsistSubMission(int32 Index);

	// ���� �̼��� ��Ȱ��ȭ�ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
		void UnsetSubMission(int32 Index);

	// ���� �̼� (��� ��ġ ����)�� ������ �� InteractionTrigger�κ��� ȣ��Ǵ� �Լ�
	UFUNCTION(BlueprintCallable)
		void DoMainMission();

	// ���� �̼��� ������ �� InteractionTrigger�κ��� ȣ��Ǵ� �Լ�
	UFUNCTION(BlueprintCallable)
		void DoSubMission(int32 Index);

	// �ӹ��� ��ġ�� ����� �� �ִ� �ð������� Ȯ�� (Ÿ�̸� 00:00 ~ 00:20, 4:40 ~ 5:00)
	UFUNCTION(BlueprintCallable)
		bool IsAboardable();

	// Arbiter beginplay �� ȣ��Ǵ� ��Ʈ�ѷ� ��� �Լ�
	UFUNCTION(BlueprintCallable)
		void RegisterArbiter(class AGamemodeArbiter* Controller);

	// ĳ���� beginplay �� ȣ��Ǵ� Ÿ�̸�/�̼� ���� ��Ʈ�ѷ� ��� �Լ�
	UFUNCTION(BlueprintCallable)
		void RegisterWidgetControllers(class UTimerWidget* Timer, class UMissionWidget* Mission);

	// ĳ���� �ӹ� ���� �� ȣ��Ǵ� �÷��̾� �ӹ� ���� �Լ� (��ġ ����, �ӹ� ���� ��)
	UFUNCTION(BlueprintCallable)
		void InitializeMission(class AAstronautCharacter* Target, int32 Mission);

	// Ư�� ��� �Լ�: �������� ȣ���Ͽ� ȭ�� ũ�ν����̵�
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void PlayCrossFade();

	// Ư�� ��� �Լ�: Ž�缱 �ܳ��� �̵��� ���� ĳ���� ��ġ ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void MoveLEM(bool bIsEntering);

public:
	// bool Ÿ������ ���� �̼� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bIsMissionDone;

	// TArray<bool> Ÿ������ ���� �̼� ���� (Expected Length = 6)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<bool> bIsSubmissionDone;

	// TArray<int> Ÿ������ �������� ���õ� ���� �̼� ���� (Expected Length = 3)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<int> RandomSubmissionIndices;

	// Text Ÿ���� ���� �̼� ���� ǥ�ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FText MainMissionText;

	// TArray<FText> Ÿ���� ���� �̼� ���� ǥ�ð� (Max Length = 3)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<FText> SubMissionText;

	// �÷��̾ ������ �� �ִ��� ���θ� ����. bMovable = false�� ��� Ÿ�̸� ���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bMovable;

	// Ÿ�̸ӿ� ǥ�õǴ� �ð��� ����. TIME_PERIOD�� ��ɼ��� �����ϴ� �� �ֱ⸦ ��Ÿ�� (���� ����: 5��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int32 Time;

private:
	// ���Ἲ�� ����� ù Ÿ�̸� ���� (1s) ���� ���� ȣ���� ���� �ӽ� ����
	bool bInitializeFlag;
};
