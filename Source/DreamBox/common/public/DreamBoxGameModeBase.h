// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../../common/public/DreamBox.h"
#include "TransitionStructBase.h"
#include "DreamBoxGameStateBase.h"
#include "GameFramework/GameModeBase.h"
#include "DreamBoxGameModeBase.generated.h"

/* 
 - Name        : ADreamBoxGamemode
 - Descirption : 메인 게임모드 베이스, 레벨 스트리밍 관련 로직이 들어있음
 - Date        : 2022/09/28 LJH
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeleDynamicNoParam);

UCLASS()
class DREAMBOX_API ADreamBoxGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayerController);

public:
	//로딩(콘텐츠 레벨 스트리밍)이 끝난 시점에 호출되는 이벤트 
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicNoParam AfterLoadingEvent;
public:
	//로딩이 끝난 이후의 BeginPlay 이벤트
	UFUNCTION()
		virtual void BeginPlayAfterLoading();

public:
	//게임 시작 Info, idx에 따라 플레이어를 구분
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		TArray<FContentStartInfo> ContentStartInfoList;

private:
	//플레이어 Controller을 저장하는 배열, idx에 따라 플레이어를 구분
	UPROPERTY()
		TArray<APlayerController*> PlayerControllerList; //0 is Host

	//플레이어 Character을 저장하는 배열, idx에 따라 플레이어를 구분
	UPROPERTY()
		TArray<class AVRCharacter*> PlayerCharacterList; 
};
