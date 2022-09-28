// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/DreamBoxGameModeBase.h"
#include "FireFighterGamemode.generated.h"

/*
 - Name        : AFirefighterGamemode
 - Descirption : Firefighter 직업군의 메인 게임모드 (미션 업데이트 및 트랜지션 위젯 이벤트 포함)
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
	//특정한 미션의 내부 데이터를 업데이트 (MissionID : 추가 및 업데이트 할 미션 ID, Variable : 미션 진행도 (슬라임1마리))
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicThreeInt UpdateMissionList;

	//데이터 시트의 ID를 기반으로 Script를 띄움
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicTwoInt ShowScriptWithID;
	
	//문자열을 기반으로 Script를 띄움 (시간은 고정)
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicIntString ShowScriptWithString;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 로딩 직후의 BeginPlay
	virtual void BeginPlayAfterLoading() override;

public:
	//완료한 미션을 셋에 추가
	UFUNCTION(BlueprintCallable)
		void AddToCompleteSet(int32 MissionID);

	//특정 미션이 완료 되었는지 판단 
	UFUNCTION(BlueprintCallable)
		bool GetMissionIsComplete(int32 MissionID);

	
	//게임 시작과 동시에 출력할 스크립트를 띄움
	UFUNCTION()
		void ShowInitialScript();

public:
	//디버그 전용 : 초기 스크립트를 띄울지?
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bShowInitScript = true;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 InitialScriptID = 1;

private:
	//완료한 미션의 ID들을 저장
	UPROPERTY()
		TSet<int32> CompleteMissionSet; 

	//플레이어 캐릭터 레퍼런스
	UPROPERTY()
		class AFirefighterCharacter* PlayerCharacterRef;

	//Delay 사용을 위한 타이머 핸들
	UPROPERTY()
		struct FTimerHandle WaitHandle;
};
