// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "Engine/LevelScriptActor.h"
#include "TransitionStructBase.h"
#include "PersistentBaseLevel.generated.h"

/*
 - Name        : APersistentBaseLevel
 - Descirption : Transition, Streaming 로직을 포함하는 Persistent 레벨의 BaseClass
 - Date        : 2022/09/24 LJH
 */

UCLASS()
class DREAMBOX_API APersistentBaseLevel : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void SetupLevelOptions();

	//특정 레벨을 로드하고, 로드 End 이벤트를 BroadCast
	UFUNCTION(BlueprintImplementableEvent)
		void LoadTargetLevelWithTransition();

	//타겟 레벨 로드가 완료 되었다면, Transition Level을 언로드
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UnloadTransitionLevel();

	//레벨 시퀀스 플레이어를 초기화
	UFUNCTION(BlueprintCallable)
		void InitLevelSequencePlayer();

	//특정 레벨 등장 시퀀스를 플레이
	UFUNCTION(BlueprintCallable)
		void PlayAppearAnimSequence(bool bIsAppearAnim);

public: 
	UFUNCTION(BlueprintCallable, BlueprintPure)
		ULevelSequencePlayer* GetLevelFadeSequencePlayer(bool bIsBegin) const { return bIsBegin ? AppearAnimSequencePlayer : DisappearAnimSequencePlayer; }
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//타이틀 등장 효과 애니메이션 시퀀스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* AppearAnimSequence;

	//타이틀 소멸 효과 애니메이션 시퀀스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* DisappearAnimSequence;

	//트랜지션 옵션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Transition Options")
		FTransitionOptionStruct TransitionOptions;

private:
	//시퀀스 플레이어 : 초기 등장 애님 시퀀스 
	UPROPERTY()
		class ULevelSequencePlayer* AppearAnimSequencePlayer;

	//시퀀스 플레이어 : 소멸 애님 시퀀스
	UPROPERTY()
		class ULevelSequencePlayer* DisappearAnimSequencePlayer;

	//게임모드 레퍼런스
	UPROPERTY()
		class ADreamBoxGameModeBase* GamemodeRef;
};
