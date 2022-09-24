// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/VRCharacter.h"
#include "FirefighterInteractionType.h"
#include "FirefighterCharacter.generated.h"

/*
 - Name        : AFirefighterCharacter
 - Descirption : Firefighter ������ ���� Playable ĳ����
 - Date        : 2022/09/24 LJH
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

	/*-------- Interaction -----------------*/
	//��ȣ�ۿ��� �õ� : bIsReadyToInteraction�� InteractionType ������� ����
	UFUNCTION()
		void TryInteraction();

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

public: // Set Get
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

	//ĳ������ Visibility�� ����
	UFUNCTION()
		void SetCharacterVisibility(bool NewState) const;

public: //Delegate ����, �÷��̾ ��ġ�� ����? - ��Ƽ�÷��� �� ���� ��� ����
	UFUNCTION()
		void UpdateMissionList(int32 PlayerID, int32 MissionID, int32 Variable);

	UFUNCTION()
		void ShowScriptWithID(int32 PlayerID, int32 ScriptID);

	UFUNCTION()
		void ShowScriptWithString(int32 PlayerID, FString Script);

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

	UPROPERTY(EditAnywhere)
		UChildActorComponent* ScriptManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UChildActorComponent* MissionManager;

private:
	//���Ӹ�� ���۷���
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef;

	//���� ĳ������ ���۷��� (InValid �� ��� �Ұ���)
	UPROPERTY()
		class AInjuredCharacter* InjuredCharacterRef;

	//ȭ�� ���� ���� ���۷��� 
	UPROPERTY()
		class ACauseOfFire* CauseOfFireRef;

	//MissionManager ���۷���
	UPROPERTY()
		class AMissionManager* MissionManagerRef;

	//ScriptManager ���۷���
	UPROPERTY()
		class AScriptManager* ScriptManagerRef;

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