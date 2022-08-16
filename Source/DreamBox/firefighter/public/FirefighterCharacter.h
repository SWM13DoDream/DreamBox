// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "../../common/public/VRCharacter.h"
#include "InjuredCharacter.h"
#include "TimerManager.h"
#include "CauseOfFire.h"
#include "FirefighterGamemode.h"
#include "FirefighterInteractionType.h"
#include "FirefighterCharacter.generated.h"

/*
 - Name        : AFirefighterCharacter
 - Descirption : Firefighter ������ ���� Playable ĳ����
 - Date        : 2022/08/16 LJH
*/

UCLASS()
class DREAMBOX_API AFirefighterCharacter : public AVRCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AFirefighterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*-------- Interaction -----------------*/
	//��ȣ�ۿ��� �õ� : bIsReadyToInteraction�� InteractionType ������� ����
	UFUNCTION()
		void TryInteraction();

	//���� �߻�
	UFUNCTION()
		void Fire();

	//�� �߻� ����
	UFUNCTION(BlueprintCallable)
		void StopFire();

	UFUNCTION(BlueprintCallable)
		void InvestigateCauseOfFire();

	//Interaction) ��ģ ĳ���͸� ����� ������
	UFUNCTION(BlueprintCallable)
		void CarryInjuredCharacter();

	//Interaction) ���� �ִ� ĳ���͸� ��������
	UFUNCTION(BlueprintCallable)
		void PutInjuredCharacter();

	//���ͷ��� �� ȭ����ξ����� ���۷��� ����
	UFUNCTION(BlueprintCallable)
		void SetCauseOfFireRef(ACauseOfFire* NewCauseOfFire);

	//���� ĳ������ ���۷����� ����
	UFUNCTION(BlueprintCallable)
		void SetInjuredCharacterRef(AInjuredCharacter* NewInjuredCharacter);

	//���ͷ��� Ÿ���� ����
	UFUNCTION(BlueprintCallable)
		void SetInteractionType(EFirefighterInteractionType NewType);

	//Interaction�� �������� ���θ� ������Ʈ
	UFUNCTION(BlueprintCallable)
		void SetIsReadyToInteraction(bool NewState);

	//�÷��̾ InjurecCharacter ��ü�� �����ִ��� ������Ʈ
	UFUNCTION()
		void SetIsCarrying(bool NewState);

	//Interaction ���� ��� �ʱ�ȭ
	UFUNCTION()
		void ResetInteractionState(); 

	//Interaction�� �������� ���� ��ȯ
	UFUNCTION(BlueprintCallable)
		bool GetIsReadyToInteraction() const { return bIsReadyToInteraction; }

	//ĳ���Ͱ� � ���� �ް� �ִ��� ��ȯ
	UFUNCTION(BlueprintCallable)
		bool GetIsCarrying() const { return bIsCarrying;  }

	//�����ִ� InjuredCharacter�� ���۷����� ��ȯ
	UFUNCTION(BlueprintCallable)
		AInjuredCharacter* GetInjuredCharacterRef() const { return InjuredCharacterRef;  }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//ĳ���Ͱ� ������ �ҹ� ȣ�� ��â
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* FireHose; 

	//�����ǰ��ִ� ĳ���Ͱ� ������ ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* RescueSocket;

	//ĳ������ ������ �Һ� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpotLightComponent* FlashLight;

private:
	//���Ӹ�� ���۷���
	UPROPERTY()
		AFirefighterGamemode* GamemodeRef;

	//���� ĳ������ ���۷��� (InValid �� ��� �Ұ���)
	UPROPERTY()
		AInjuredCharacter* InjuredCharacterRef;

	//ȭ�� ���� ���� ���۷��� 
	UPROPERTY()
		ACauseOfFire* CauseOfFireRef;

	//C++ ������ ��� ���� Ÿ�̸� �ڵ� : �̻��
	UPROPERTY()
		FTimerHandle WaitHandle;

	//���� ������ InteractionType
	UPROPERTY()
		EFirefighterInteractionType InteractionType;

	//���� ���� �ִ���?
	UPROPERTY()
		bool bIsCarrying;

	//��ȣ�ۿ��� �����Ѱ�?
	UPROPERTY()
		bool bIsReadyToInteraction;
};