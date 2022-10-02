// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "FirefighterInteractionType.h"
#include "FirefighterCharacter.generated.h"

/*
 - Name        : AFirefighterCharacter
 - Descirption : Firefighter ������ ���� Playable ĳ����
 - Date        : 2022/09/29 LJH
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

/// ======================================
/// ��ȣ�ۿ� ���� �Լ�
/// ======================================
public:
	//��ȣ�ۿ��� �õ� : bIsReadyToInteraction�� InteractionType ������� ����
	UFUNCTION()
		void TryInteraction();

	//Grab State L ���¸� üũ�ϰ� ���� �߻� �õ�
	UFUNCTION()
		void TryFireL();

	//Grab State R ���¸� üũ�ϰ� ���� �߻� �õ�
	UFUNCTION()
		void TryFireR();

	//��ȣ�ۿ� : ���� �߻�
	UFUNCTION()
		void Fire();

	//��ȣ�ۿ� : �� �߻� ����
	UFUNCTION(BlueprintCallable)
		void StopFire();

	//��ȣ�ۿ� : ȭ�� ���� ����
	UFUNCTION(BlueprintCallable)
		void InvestigateCauseOfFire();

	//��ȣ�ۿ� : ��ģ ĳ���͸� ����� ������
	UFUNCTION(BlueprintCallable)
		void CarryInjuredCharacter();

	//��ȣ�ۿ� : ���� �ִ� ĳ���͸� ��������
	UFUNCTION(BlueprintCallable)
		void PutInjuredCharacter();
	
	//Interaction ���� ��� �ʱ�ȭ
	UFUNCTION()
		void ResetInteractionState();

/// ======================================
///  Read, Write 
/// ======================================
public:
	//��ȣ�ۿ� �� ȭ����ξ����� ���۷��� ����
	UFUNCTION(BlueprintCallable)
		void SetCauseOfFireRef(ACauseOfFire* NewCauseOfFire) { CauseOfFireRef = NewCauseOfFire; }

	//���� ĳ������ ���۷����� ����
	UFUNCTION(BlueprintCallable)
		void SetInjuredCharacterRef(AInjuredCharacter* NewInjuredCharacter) { InjuredCharacterRef = NewInjuredCharacter; }

	//���ͷ��� Ÿ���� ����
	UFUNCTION(BlueprintCallable)
		void SetInteractionType(EFirefighterInteractionType NewType) { InteractionType = NewType; }

	//Interaction�� �������� ���θ� ������Ʈ
	UFUNCTION(BlueprintCallable)
		void SetIsReadyToInteraction(bool NewState) { bIsReadyToInteraction = NewState; }

	//�÷��̾ InjurecCharacter ��ü�� �����ִ��� ������Ʈ
	UFUNCTION()
		void SetIsCarrying(bool NewState) { bIsCarrying = NewState; }

	//ȣ���� ��� �ִ� ����(�޼�, ������, None)�� ����
	UFUNCTION(BlueprintCallable)
		void SetHoseGrabState(EFirefighterHoseGrabState NewState);

	//ȣ���� ��� �ִ����� ���¸� ��ȯ
	UFUNCTION(BlueprintCallable, BlueprintPure)
		EFirefighterHoseGrabState GetCurrentState() { return HoseGrabState; }

	UFUNCTION(BlueprintCallable)
		void SetFireHoseRef(AFireHose* NewFireHose);

	//Interaction�� �������� ���� ��ȯ
	UFUNCTION(BlueprintCallable)
		bool GetIsReadyToInteraction() const { return bIsReadyToInteraction; }

	//ĳ���Ͱ� � ���� �ް� �ִ��� ��ȯ
	UFUNCTION(BlueprintCallable)
		bool GetIsCarrying() const { return bIsCarrying;  }

	//�����ִ� InjuredCharacter�� ���۷����� ��ȯ
	UFUNCTION(BlueprintCallable)
		AInjuredCharacter* GetInjuredCharacterRef() const { return InjuredCharacterRef;  }

	//ĳ������ Visibility�� ����
	UFUNCTION()
		void SetCharacterVisibility(bool NewState) const;

/// =================================
/// �̼� �̺�Ʈ / �ε� �̺�Ʈ ����
/// =================================
public: 
	UFUNCTION()
		void UpdateMissionList(int32 PlayerID, int32 MissionID, int32 Variable);

	UFUNCTION()
		void ShowScriptWithID(int32 PlayerID, int32 ScriptID);

	UFUNCTION()
		void ShowScriptWithString(int32 PlayerID, FString Script);

	UFUNCTION()
		virtual void PreLoadingEnd() override;

public:
	//�����ǰ��ִ� ĳ���Ͱ� ������ ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* RescueSocket;

	//ĳ������ ������ �Һ� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpotLightComponent* FlashLight;

	UPROPERTY(EditAnywhere)
		UChildActorComponent* ScriptManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UChildActorComponent* MissionManager;

private:
	//���� ĳ������ ���۷��� (InValid �� ��� �Ұ���)
	UPROPERTY()
		class AInjuredCharacter* InjuredCharacterRef;

	UPROPERTY()
		class AFirefighterGamemode* FirefighterGamemodeRef;

	//ȭ�� ���� ���� ���۷��� 
	UPROPERTY()
		class ACauseOfFire* CauseOfFireRef;

	//MissionManager ���۷���
	UPROPERTY()
		class AMissionManager* MissionManagerRef;

	//ScriptManager ���۷���
	UPROPERTY()
		class AScriptManager* ScriptManagerRef;

	//ĳ���Ͱ� ������ �ҹ� ȣ�� ��â
	UPROPERTY()
		AFireHose* FireHoseRef;

	//���� ������ InteractionType
	UPROPERTY()
		EFirefighterInteractionType InteractionType;

	UPROPERTY()
		EFirefighterHoseGrabState HoseGrabState; 

	//���� ���� �ִ���?
	UPROPERTY()
		bool bIsCarrying;

	//��ȣ�ۿ��� �����Ѱ�?
	UPROPERTY()
		bool bIsReadyToInteraction;
};