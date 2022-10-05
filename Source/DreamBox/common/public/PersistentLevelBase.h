// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "Engine/LevelScriptActor.h"
#include "TransitionStructBase.h"
#include "PersistentLevelBase.generated.h"

/*
 - Name        : APersistentLevelBase
 - Descirption : Transition, Streaming ������ �����ϴ� Persistent ������ BaseClass
 - Date        : 2022/10/04 LJH
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeleDynamicLoading);
//DECLARE_DYNAMIC_MULTICASE_DELEGATE_OneParam(FDeleDynamicLoadingTest, APlayerController, PlayerController);

UCLASS()
class DREAMBOX_API APersistentLevelBase : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	//�ε�(������ ���� ��Ʈ����) ������ ȣ��Ǵ� �̺�Ʈ
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicLoading PreLoadingEndDelegate;

	//�ε�(������ ���� ��Ʈ����)�� ���� ������ ȣ��Ǵ� �̺�Ʈ 
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicLoading PostLoadingDelegate;

public:
	UFUNCTION(BlueprintCallable)
		void SetupLevelOptions();

	//Ư�� ������ �ε��ϰ�, �ε� End �̺�Ʈ�� BroadCast
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void LoadTargetLevel();

	//Ÿ�� ���� �ε尡 �Ϸ� �Ǿ��ٸ�, Transition Level�� ��ε�
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UnloadTransitionLevel();

	//�ε��� �������� �˸��� �̺�Ʈ�� BroadCast
	UFUNCTION(BlueprintCallable)
		void BroadcastPostLoadingEvent();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
		class ADreamBoxGameModeBase* GetGamemodeRef() { return GamemodeRef; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Ʈ������ �ɼ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Transition Options")
		FTransitionOptionStruct TransitionOptions;

private:
	//���Ӹ�� ���۷���
	UPROPERTY()
		class ADreamBoxGameModeBase* GamemodeRef;
};