// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "FireFighterGamemode.generated.h"

/*
 - Name        : AFirefighterGamemode
 - Descirption : Firefighter �������� ���� ���Ӹ�� (�̼� ������Ʈ �� Ʈ������ ���� �̺�Ʈ ����)
 - Date        : 2022/09/03 LJH
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleDynamicThreeInt, int32, PlayerID, int32, MissionID, int32, Variable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeleDynamicTwoInt, int32, PlayerID, int32, ScriptID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeleDynamicIntString, int32, PlayerID, FString, Script);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleDynamicOneParam, int32, PlayerID);


UCLASS()
class DREAMBOX_API AFirefighterGamemode : public AGameModeBase
{
	GENERATED_BODY()
public:
	//Ư���� �̼��� ���� �����͸� ������Ʈ (MissionID : �߰� �� ������Ʈ �� �̼� ID, Variable : �̼� ���൵ (������1����))
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicThreeInt UpdateMissionList;

	//������ ��Ʈ�� ID�� ������� Script�� ���
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicTwoInt ShowScriptWithID;
	
	//���ڿ��� ������� Script�� ��� (�ð��� ����)
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicIntString ShowScriptWithString;

	//CrossFade �ִϸ��̼��� ���
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicOneParam CrossFadeAnimationEvent; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//�Ϸ��� �̼��� �¿� �߰�
	UFUNCTION(BlueprintCallable)
		void AddToCompleteSet(int32 MissionID);

	//Ư�� �̼��� �Ϸ� �Ǿ����� �Ǵ� 
	UFUNCTION(BlueprintCallable)
		bool GetMissionIsComplete(int32 MissionID);

	//���� �������� �ʱ�ȭ
	UFUNCTION()
		void InitLevelSequence();

	//���� ���۰� ���ÿ� ����� ��ũ��Ʈ�� ���
	UFUNCTION()
		void ShowInitialScript();

	//ũ�ν� ���̵带 ������ ����ϴ� ����
	UFUNCTION(BlueprintCallable)
		void PlayCrossFadeAnim(int32 PlayerID);

public:
	//ũ�ν� ���̵� ȿ�� 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* CrossFade;

	//����� ���� : �ʱ� ��ũ��Ʈ�� �����?
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bShowInitScript = true;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 InitialScriptID = 1;

private:
	//�Ϸ��� �̼��� ID���� ����
	UPROPERTY()
		TSet<int32> CompleteMissionSet; 

	//������ �÷��̾�
	UPROPERTY()
		class ULevelSequencePlayer* CrossFadePlayer;

	//�÷��̾� ĳ���� ���۷���
	UPROPERTY()
		ACharacter* PlayerCharacterRef;

	//Delay ����� ���� Ÿ�̸� �ڵ�
	UPROPERTY()
		struct FTimerHandle WaitHandle;
};