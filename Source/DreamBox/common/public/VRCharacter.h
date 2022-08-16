// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

/*
 - Name        : AVRCharacter
 - Descirption : ���� Playable VR ĳ���� Base
 - Date        : 2022/08/16 LJH
*/

UCLASS()
class DREAMBOX_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�⺻ �̵� �Լ� : �յ� �̵�
	UFUNCTION()
		void MoveForward(float Value);

	//�⺻ �̵� �Լ� : �翷 �̵�
	UFUNCTION()
		void MoveRight(float Value);

	//�⺻ ȸ�� �Լ� : ���������� 45�� ��ŭ ī�޶� ��ȯ
	UFUNCTION()
		void SnapTurnLeft();

	//�⺻ ȸ�� �Լ� : ���������� 45�� ��ŭ ī�޶� ��ȯ
	UFUNCTION()
		void SnapTurnRight();

	//SnapTurn�� �������� �ԷµǴ� ���� �����ϴ� �Լ�
	UFUNCTION()
		void ResetSnapTurn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//VR Immersive ���� ����� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* VROrigin;

	//VR Immersive ���� ����� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* SpectatorRef;

	//ĳ������ ���� ī�޶� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* FollowingCamera;

private:
	//SnapTurn ������ ��������? (���� �Է� ����)
	UPROPERTY()
		bool bSnapTurnIsFinished;
};
