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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleDynamicIntBool, int32, PlayerID, int32, MissionID, bool, bIsRemoveTarget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleDynamicTwoInt, int32, PlayerID, int32, MissionID, int32, NewCondition);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleDynamicNoParam, int32, PlayerID);


UCLASS()
class DREAMBOX_API AFirefighterGamemode : public AGameModeBase
{
	GENERATED_BODY()
public:
	//미션을 업데이트 한다. (새로운 미션 추가 및 제거)
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicIntBool UpdateMissionList;
	
	//특정한 미션의 내부 데이터를 업데이트
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicTwoInt UpdateMissionListComponent;

	//FadeInOut 애니메이션을 출력
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicNoParam PlayFadeInOutAnimation; 
};
