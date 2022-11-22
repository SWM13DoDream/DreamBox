// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../../common/public/DreamBox.h"
#include "TransitionStructBase.h"
#include "DreamBoxGameModeBase.generated.h"

/* 
 - Name        : ADreamBoxGamemode
 - Descirption : ���� ���Ӹ�� ���̽�, ���� ��Ʈ���� ���� ������ �������
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
	//�ε��� ���� ������ BeginPlay �̺�Ʈ
	virtual void PostLoadingEvent();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetPlayerControllerCount() { return PlayerControllerList.Num(); }
	
	//Level Script ���۷����� ��ȯ
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
	//���� ���� Info, idx�� ���� �÷��̾ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		TArray<FContentStartInfo> ContentStartInfoList;

protected:
	//�÷��̾��� �ε� ������ ��Ÿ���� �迭
	UPROPERTY()
		TArray<bool> PlayerLoadStateList;

protected:
	//�÷��̾� Controller�� �����ϴ� �迭, idx�� ���� �÷��̾ ����
	UPROPERTY()
		TArray<APlayerController*> PlayerControllerList; //0 is Host

	//�÷��̾� Character�� �����ϴ� �迭, idx�� ���� �÷��̾ ����
	UPROPERTY()
		TArray<class AVRCharacter*> PlayerCharacterList; 


	UPROPERTY()
		class APersistentLevelBase* LevelScriptRef;

	//Multipleyr(Host) ���� Property : ���� �ε� ���� (Client���� Sync ����)
	UPROPERTY()
		EPersistentLoadStateType CurrentLoadState = EPersistentLoadStateType::E_PreLoad;
};
