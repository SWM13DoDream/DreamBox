// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FireFighterGamemode.generated.h"

/*
 - Name        : AFirefighterGamemode
 - Descirption : Firefighter �������� ���� ���Ӹ�� (�̼� ������Ʈ �� Ʈ������ ���� �̺�Ʈ ����)
 - Date        : 2022/07/20 LJH
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleDynamicTwoIntBool, int32, PlayerID, int32, MissionID, bool, bIsRemoveTarget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleDynamicThreeInt, int32, PlayerID, int32, MissionID, int32, NewCondition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeleDynamicTwoInt, int32, PlayerID, int32, ScriptID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeleDynamicIntString, int32, PlayerID, FString, Script);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleDynamicOneParam, int32, PlayerID);


UCLASS()
class DREAMBOX_API AFirefighterGamemode : public AGameModeBase
{
	GENERATED_BODY()
public:
	//�̼��� ������Ʈ �Ѵ�. (���ο� �̼� �߰� �� ����)
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicTwoIntBool UpdateMissionList;
	
	//Ư���� �̼��� ���� �����͸� ������Ʈ
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicThreeInt UpdateMissionListComponent;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicTwoInt ShowScriptWithID;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicIntString ShowScriptWithString;

	//FadeInOut �ִϸ��̼��� ���
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicOneParam PlayFadeInOutAnimation; 

public:
	//�Ϸ��� �̼��� �¿� �߰�
	UFUNCTION(BlueprintCallable)
		void AddToCompleteSet(int32 MissionID);

	//Ư�� �̼��� �Ϸ� �Ǿ����� �Ǵ� 
	UFUNCTION(BlueprintCallable)
		bool GetMissionIsComplete(int32 MissionID);

private:
	//�Ϸ��� �̼��� ID���� ����
	UPROPERTY()
		TSet<int32> CompleteMissionSet; 
};
