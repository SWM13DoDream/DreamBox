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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleDynamicIntBool, int32, PlayerID, int32, MissionID, bool, bIsRemoveTarget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleDynamicTwoInt, int32, PlayerID, int32, MissionID, int32, NewCondition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleDynamicNoParam, int32, PlayerID);


UCLASS()
class DREAMBOX_API AFirefighterGamemode : public AGameModeBase
{
	GENERATED_BODY()
public:
	//�̼��� ������Ʈ �Ѵ�. (���ο� �̼� �߰� �� ����)
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicIntBool UpdateMissionList;
	
	//Ư���� �̼��� ���� �����͸� ������Ʈ
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicTwoInt UpdateMissionListComponent;

	//FadeInOut �ִϸ��̼��� ���
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicNoParam PlayFadeInOutAnimation; 
};
