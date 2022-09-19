// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

/*
 - Name        : AVRCharacter
 - Descirption : ���� Playable VR ĳ���� Base
 - Date        : 2022/09/01 LJH
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

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//�⺻ �̵� �Լ� : �յ� �̵�
	UFUNCTION()
		void MoveForward(float Value);

	//�⺻ �̵� �Լ� : �翷 �̵�
	UFUNCTION()
		void MoveRight(float Value);

	//�⺻ ȸ�� �Լ� : 45�� ��ŭ ī�޶� ��ȯ
	UFUNCTION()
		void SnapTurn(float Value);

	//SnapTurn�� �������� �ԷµǴ� ���� �����ϴ� �Լ�
	UFUNCTION()
		void ResetSnapTurn();

	//Jump�� Ȱ��ȭ/��Ȱ��ȭ ��
	UFUNCTION()
		void SetCanJump(bool NewState);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//VR Immersive ���� ����� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* VROrigin;

	//ĳ������ ���� ī�޶� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* FollowingCamera;

	//VR Immersive ���� ����� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* SpectatorRef;

	//VR Immersive ���� ����� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* GenericHMD;

	//VR Immersive ���� ����� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* HeadCollision;

	//VR Immersive ���� ����� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetInteractionComponent* WidgetInteraction;
	
	//C++ ������ ��� ���� Ÿ�̸� �ڵ� 
	UPROPERTY()
		struct FTimerHandle WaitHandle;

	//������ ��������? (BP���� �ɼ� ����, �⺻�� : t)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
		bool bCanJump = true; 


private:
	//SnapTurn ������ ��������? (���� �Է� ����)
	UPROPERTY()
		bool bSnapTurnIsFinished;
};
