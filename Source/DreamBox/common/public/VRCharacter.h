// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

<<<<<<< HEAD
#include "DreamBox.h"
#include "GameFramework/Character.h"
=======
#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "Components/WidgetInteractionComponent.h"
>>>>>>> 37667fc1c8371a3dc5717464c7a857d6d5968402
#include "VRCharacter.generated.h"

/*
 - Name        : AVRCharacter
 - Descirption : ���� Playable VR ĳ���� Base
<<<<<<< HEAD
 - Date        : 2022/09/01 LJH
=======
 - Date        : 2022/08/20 LJH
>>>>>>> 37667fc1c8371a3dc5717464c7a857d6d5968402
*/

UCLASS()
class DREAMBOX_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();
<<<<<<< HEAD
	
=======

>>>>>>> 37667fc1c8371a3dc5717464c7a857d6d5968402
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

<<<<<<< HEAD
public:	
=======
public:
>>>>>>> 37667fc1c8371a3dc5717464c7a857d6d5968402
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
<<<<<<< HEAD
		class UWidgetInteractionComponent* WidgetInteraction;
	
	//C++ ������ ��� ���� Ÿ�̸� �ڵ� 
	UPROPERTY()
		struct FTimerHandle WaitHandle;
=======
		UWidgetInteractionComponent* WidgetInteraction;

	//C++ ������ ��� ���� Ÿ�̸� �ڵ� 
	UPROPERTY()
		FTimerHandle WaitHandle;
>>>>>>> 37667fc1c8371a3dc5717464c7a857d6d5968402

private:
	//SnapTurn ������ ��������? (���� �Է� ����)
	UPROPERTY()
		bool bSnapTurnIsFinished;
};
