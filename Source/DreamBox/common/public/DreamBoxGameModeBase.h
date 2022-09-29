// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../../common/public/DreamBox.h"
#include "TransitionStructBase.h"
#include "DreamBoxGameModeBase.generated.h"

/* 
 - Name        : ADreamBoxGamemode
 - Descirption : 메인 게임모드 베이스, 레벨 스트리밍 관련 로직이 들어있음
 - Date        : 2022/09/29 LJH
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
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetPlayerControllerCount() { return PlayerControllerList.Num(); }

public:
	//로딩이 끝난 이후의 BeginPlay 이벤트
	UFUNCTION()
		virtual void PostLoadingEvent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		class APersistentLevelBase* GetLevelScriptRef() { return LevelScriptRef; }

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

	UPROPERTY()
		class APersistentLevelBase* LevelScriptRef;
};
