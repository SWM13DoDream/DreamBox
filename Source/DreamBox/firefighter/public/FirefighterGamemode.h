// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FireFighterGamemode.generated.h"

/*
 - Name        : AFirefighterGamemode
 - Descirption : Firefighter 직업군의 메인 게임모드 (미션 업데이트 및 트랜지션 위젯 이벤트 포함)
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
	//미션을 업데이트 한다. (새로운 미션 추가 및 제거)
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicTwoIntBool UpdateMissionList;
	
	//특정한 미션의 내부 데이터를 업데이트
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicThreeInt UpdateMissionListComponent;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicTwoInt ShowScriptWithID;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicIntString ShowScriptWithString;

	//FadeInOut 애니메이션을 출력
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicOneParam PlayFadeInOutAnimation; 

public:
	//완료한 미션을 셋에 추가
	UFUNCTION(BlueprintCallable)
		void AddToCompleteSet(int32 MissionID);

	//특정 미션이 완료 되었는지 판단 
	UFUNCTION(BlueprintCallable)
		bool GetMissionIsComplete(int32 MissionID);

private:
	//완료한 미션의 ID들을 저장
	UPROPERTY()
		TSet<int32> CompleteMissionSet; 
};
