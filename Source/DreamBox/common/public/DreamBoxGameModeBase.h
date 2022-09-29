// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../../common/public/DreamBox.h"
#include "TransitionStructBase.h"
#include "DreamBoxGameModeBase.generated.h"

/* 
 - Name        : ADreamBoxGamemode
 - Descirption : ���� ���Ӹ�� ���̽�, ���� ��Ʈ���� ���� ������ �������
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
	//�ε��� ���� ������ BeginPlay �̺�Ʈ
	UFUNCTION()
		virtual void PostLoadingEvent();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		class APersistentLevelBase* GetLevelScriptRef() { return LevelScriptRef; }

public:
	//���� ���� Info, idx�� ���� �÷��̾ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		TArray<FContentStartInfo> ContentStartInfoList;

private:
	//�÷��̾� Controller�� �����ϴ� �迭, idx�� ���� �÷��̾ ����
	UPROPERTY()
		TArray<APlayerController*> PlayerControllerList; //0 is Host

	//�÷��̾� Character�� �����ϴ� �迭, idx�� ���� �÷��̾ ����
	UPROPERTY()
		TArray<class AVRCharacter*> PlayerCharacterList; 

	UPROPERTY()
		class APersistentLevelBase* LevelScriptRef;
};
