// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "Engine/LevelScriptActor.h"
#include "TransitionStructBase.h"
#include "PersistentLevelBase.generated.h"

/*
 - Name        : APersistentLevelBase
 - Descirption : Transition, Streaming 로직을 포함하는 Persistent 레벨의 BaseClass
 - Date        : 2022/09/29 LJH
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeleDynamicLoading);

UCLASS()
class DREAMBOX_API APersistentLevelBase : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicLoading PreLoadingEnd;

	//로딩(콘텐츠 레벨 스트리밍)이 끝난 시점에 호출되는 이벤트 
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicLoading PostLoadingEvent;

public:
	UFUNCTION(BlueprintCallable)
		void SetupLevelOptions();

	//특정 레벨을 로드하고, 로드 End 이벤트를 BroadCast
	UFUNCTION(BlueprintImplementableEvent)
		void LoadTargetLevel();

	//타겟 레벨 로드가 완료 되었다면, Transition Level을 언로드
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UnloadTransitionLevel();

	//로딩이 끝났음을 알리는 이벤트를 BroadCast
	UFUNCTION(BlueprintCallable)
		void BroadcastPostLoadingEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//트랜지션 옵션
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Transition Options")
		FTransitionOptionStruct TransitionOptions;

private:
	//게임모드 레퍼런스
	UPROPERTY()
		class ADreamBoxGameModeBase* GamemodeRef;
};
