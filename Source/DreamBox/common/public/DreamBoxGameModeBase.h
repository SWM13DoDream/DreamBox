// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../../common/public/DreamBox.h"
#include "TransitionStructBase.h"
#include "DreamBoxGameModeBase.generated.h"

/* 
 - Name        : ADreamBoxGamemode
 - Descirption : 메인 게임모드 베이스, 레벨 스트리밍 관련 로직이 들어있음
 - Date        : 2022/10/04 LJH
 */


UENUM(BlueprintType)
enum class EPersistentLoadStateType : uint8
{
	E_PreLoad = 0		UMETA(DisplayName = "PreLoad"),
	E_InLoad			UMETA(DisplayName = "InLoad"),
	E_PostLoad			UMETA(DisplayName = "PostLoad")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeleDynamicNoParam);

UCLASS()
class DREAMBOX_API ADreamBoxGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PostLogin(APlayerController* NewPlayerController);
	
	UFUNCTION(BlueprintCallable)
	virtual void PreLoadingEndEvent();

	UFUNCTION(BlueprintCallable)
	//로딩이 끝난 이후의 BeginPlay 이벤트
	virtual void PostLoadingEvent();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetPlayerControllerCount() { return PlayerControllerList.Num(); }
	
	//Level Script 레퍼런스를 반환
	UFUNCTION(BlueprintCallable, BlueprintPure)
		class APersistentLevelBase* GetLevelScriptRef() { return LevelScriptRef; }

	UFUNCTION()
		void InitLevelScriptRef(class APersistentLevelBase* NewScriptRef);

	UFUNCTION(BlueprintCallable)
		void SetCurrentLoadState(EPersistentLoadStateType NewState) { CurrentLoadState = NewState; }

	UFUNCTION(BlueprintCallable)
		EPersistentLoadStateType GetCurrentLoadState() { return CurrentLoadState; }

	UFUNCTION()
		TArray<APlayerController*> GetPlayerControllerList() { return PlayerControllerList; }

	UFUNCTION()
		TArray<class AVRCharacter*> GetPlayerCharacterList() { return PlayerCharacterList; }

	UFUNCTION()
		FContentStartInfo GetPlayerStartInfo(int32 PlayerID);

	UFUNCTION(BlueprintImplementableEvent)
		void DebugMessage(float num);

public:
	//게임 시작 Info, idx에 따라 플레이어를 구분
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		TArray<FContentStartInfo> ContentStartInfoList;

protected:
	//플레이어의 로드 정보를 나타내는 배열
	UPROPERTY()
		TArray<bool> PlayerLoadStateList;

protected:
	//플레이어 Controller을 저장하는 배열, idx에 따라 플레이어를 구분
	UPROPERTY()
		TArray<APlayerController*> PlayerControllerList; //0 is Host

	//플레이어 Character을 저장하는 배열, idx에 따라 플레이어를 구분
	UPROPERTY()
		TArray<class AVRCharacter*> PlayerCharacterList; 


	UPROPERTY()
		class APersistentLevelBase* LevelScriptRef;

	//Multipleyr(Host) 전용 Property : 현재 로드 상태 (Client와의 Sync 위함)
	UPROPERTY()
		EPersistentLoadStateType CurrentLoadState = EPersistentLoadStateType::E_PreLoad;
};
