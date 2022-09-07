// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "FireFighterGamemode.generated.h"

/*
 - Name        : AFirefighterGamemode
 - Descirption : Firefighter 직업군의 메인 게임모드 (미션 업데이트 및 트랜지션 위젯 이벤트 포함)
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
	//특정한 미션의 내부 데이터를 업데이트 (MissionID : 추가 및 업데이트 할 미션 ID, Variable : 미션 진행도 (슬라임1마리))
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicThreeInt UpdateMissionList;

	//데이터 시트의 ID를 기반으로 Script를 띄움
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicTwoInt ShowScriptWithID;
	
	//문자열을 기반으로 Script를 띄움 (시간은 고정)
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicIntString ShowScriptWithString;

	//CrossFade 애니메이션을 출력
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicOneParam CrossFadeAnimationEvent; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//완료한 미션을 셋에 추가
	UFUNCTION(BlueprintCallable)
		void AddToCompleteSet(int32 MissionID);

	//특정 미션이 완료 되었는지 판단 
	UFUNCTION(BlueprintCallable)
		bool GetMissionIsComplete(int32 MissionID);

	//레벨 시퀀스를 초기화
	UFUNCTION()
		void InitLevelSequence();

	//게임 시작과 동시에 출력할 스크립트를 띄움
	UFUNCTION()
		void ShowInitialScript();

	//크로스 페이드를 실제로 출력하는 로직
	UFUNCTION(BlueprintCallable)
		void PlayCrossFadeAnim(int32 PlayerID);

public:
	//크로스 페이드 효과 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* CrossFade;

	//디버그 전용 : 초기 스크립트를 띄울지?
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bShowInitScript = true;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 InitialScriptID = 1;

private:
	//완료한 미션의 ID들을 저장
	UPROPERTY()
		TSet<int32> CompleteMissionSet; 

	//시퀀스 플레이어
	UPROPERTY()
		class ULevelSequencePlayer* CrossFadePlayer;

	//플레이어 캐릭터 레퍼런스
	UPROPERTY()
		ACharacter* PlayerCharacterRef;

	//Delay 사용을 위한 타이머 핸들
	UPROPERTY()
		struct FTimerHandle WaitHandle;
};
