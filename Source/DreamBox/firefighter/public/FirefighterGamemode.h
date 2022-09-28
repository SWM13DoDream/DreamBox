// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/DreamBoxGameModeBase.h"
#include "FireFighterGamemode.generated.h"

/*
 - Name        : AFirefighterGamemode
 - Descirption : Firefighter �������� ���� ���Ӹ�� (�̼� ������Ʈ �� Ʈ������ ���� �̺�Ʈ ����)
 - Date        : 2022/09/26 LJH
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleDynamicThreeInt, int32, PlayerID, int32, MissionID, int32, Variable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeleDynamicTwoInt, int32, PlayerID, int32, ScriptID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeleDynamicIntString, int32, PlayerID, FString, Script);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleDynamicOneParam, int32, PlayerID);


UCLASS()
class DREAMBOX_API AFirefighterGamemode : public ADreamBoxGameModeBase
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �ε� ������ BeginPlay
	virtual void BeginPlayAfterLoading() override;

public:
	//�Ϸ��� �̼��� �¿� �߰�
	UFUNCTION(BlueprintCallable)
		void AddToCompleteSet(int32 MissionID);

	//Ư�� �̼��� �Ϸ� �Ǿ����� �Ǵ� 
	UFUNCTION(BlueprintCallable)
		bool GetMissionIsComplete(int32 MissionID);

	
	//���� ���۰� ���ÿ� ����� ��ũ��Ʈ�� ���
	UFUNCTION()
		void ShowInitialScript();

public:
	//����� ���� : �ʱ� ��ũ��Ʈ�� �����?
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bShowInitScript = true;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 InitialScriptID = 1;

private:
	//�Ϸ��� �̼��� ID���� ����
	UPROPERTY()
		TSet<int32> CompleteMissionSet; 

	//�÷��̾� ĳ���� ���۷���
	UPROPERTY()
		class AFirefighterCharacter* PlayerCharacterRef;

	//Delay ����� ���� Ÿ�̸� �ڵ�
	UPROPERTY()
		struct FTimerHandle WaitHandle;
};
