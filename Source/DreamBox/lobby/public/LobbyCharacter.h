// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/VRCharacter.h"
#include "LobbyCharacter.generated.h"

/*
 - Name        : ALobbyCharacter
 - Descirption : Lobby �������� ���� Playable ĳ����
 - Date        : 2022/09/28 LJH
*/

UCLASS()
class DREAMBOX_API ALobbyCharacter : public AVRCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALobbyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//���� �������� �ʱ�ȭ
	virtual void InitLevelSequence() override;

	//virtual void OnRPCStartContent(int32 PlayerID, FContentStartInfo StartInfo);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//ũ�ν� ���̵� + �κ� ���� ������ �ִ�
	UFUNCTION(BlueprintImplementableEvent)
		void PlayLobbyInitSequenceAnim();

	//�κ� ���� ������ �ִ� ���, PlayLobbyInitSequenceAnim���� ȣ��
	UFUNCTION(BlueprintCallable)
		void PlayLobbyAppearAnim();

	//���Ӹ�� ���۷����� ���� ��ũ��Ʈ ���۷����� �ʱ�ȭ
	UFUNCTION()
		void InitLevelScriptRef();

	//���� ��ũ��Ʈ�� UnloadTransitionLevel�� ȣ��
	UFUNCTION(BlueprintCallable)
		void CallLevelLoadEndEvent();

public:	
	//�κ� ���� ȿ�� �ִϸ��̼� ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* LobbyBeginAnimSequence;

private: 
	//������ �÷��̾� : �ʱ� ���� �ִ� ������ 
	UPROPERTY()
		class ULevelSequencePlayer* LobbyBeginAnimSequencePlayer;

	UPROPERTY()
		class APersistentLevelBase* LevelScriptRef;
};
