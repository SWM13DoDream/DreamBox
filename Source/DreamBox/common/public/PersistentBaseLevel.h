// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "Engine/LevelScriptActor.h"
#include "TransitionStructBase.h"
#include "PersistentBaseLevel.generated.h"

/*
 - Name        : APersistentBaseLevel
 - Descirption : Transition, Streaming ������ �����ϴ� Persistent ������ BaseClass
 - Date        : 2022/09/24 LJH
 */

UCLASS()
class DREAMBOX_API APersistentBaseLevel : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void SetupLevelOptions();

	//Ư�� ������ �ε��ϰ�, �ε� End �̺�Ʈ�� BroadCast
	UFUNCTION(BlueprintImplementableEvent)
		void LoadTargetLevelWithTransition();

	//Ÿ�� ���� �ε尡 �Ϸ� �Ǿ��ٸ�, Transition Level�� ��ε�
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UnloadTransitionLevel();

	//���� ������ �÷��̾ �ʱ�ȭ
	UFUNCTION(BlueprintCallable)
		void InitLevelSequencePlayer();

	//Ư�� ���� ���� �������� �÷���
	UFUNCTION(BlueprintCallable)
		void PlayAppearAnimSequence(bool bIsAppearAnim);

public: 
	UFUNCTION(BlueprintCallable, BlueprintPure)
		ULevelSequencePlayer* GetLevelFadeSequencePlayer(bool bIsBegin) const { return bIsBegin ? AppearAnimSequencePlayer : DisappearAnimSequencePlayer; }
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Ÿ��Ʋ ���� ȿ�� �ִϸ��̼� ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* AppearAnimSequence;

	//Ÿ��Ʋ �Ҹ� ȿ�� �ִϸ��̼� ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* DisappearAnimSequence;

	//Ʈ������ �ɼ�
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Transition Options")
		FTransitionOptionStruct TransitionOptions;

private:
	//������ �÷��̾� : �ʱ� ���� �ִ� ������ 
	UPROPERTY()
		class ULevelSequencePlayer* AppearAnimSequencePlayer;

	//������ �÷��̾� : �Ҹ� �ִ� ������
	UPROPERTY()
		class ULevelSequencePlayer* DisappearAnimSequencePlayer;

	//���Ӹ�� ���۷���
	UPROPERTY()
		class ADreamBoxGameModeBase* GamemodeRef;
};
