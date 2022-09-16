// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/VRCharacter.h"
#include "AstronautCharacter.generated.h"

/*
 - Name			: AAstronautCharacter
 - Author		: DEVroar
 - Descirption	: ���ֺ���� Default Pawn (�÷��̾� ĳ����)
 - Date			: 2022/07/26
*/

UCLASS()
class DREAMBOX_API AAstronautCharacter : public AVRCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAstronautCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	// ���ͷ��� Ű Press�� ���ε�
	UFUNCTION()
		void OnInteract();

	// ���ͷ��� Ű Release�� ���ε�
	UFUNCTION()
		void ReleaseInteract();

public:
	// �ӹ� ����
	UFUNCTION(BlueprintCallable)
		void InitializeMission();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// ĳ���� �����Ʈ ������Ʈ (BeginPlay���� �ʱ�ȭ)
	UCharacterMovementComponent* Movement;

	// �÷��̾ ������ �ӹ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SelectedMission;

	// �÷��̾��� �̵� ��� (CSM �ӹ����� ���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MoveType;

public:
	// Ư�� Ű (Meta Quest 2 - R��Ʈ�ѷ� AŰ) �Է� �Լ�
	UFUNCTION(BlueprintCallable)
		void OnSpecialKey();

	UFUNCTION(BlueprintCallable)
		void ReleaseSpecialKey();

// LEM �ӹ� ���� ���� ������Ʈ (CSM �ӹ� �߿��� not available)  
public:
	// ĳ���� VR Origin�� �����Ǵ� Ÿ�̸� ǥ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* TimerWidget;

	// ĳ���� VR Origin�� �����Ǵ� �̼� ǥ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionWidget;

// CSM �ӹ� ���� ���� ������Ʈ (LEM �ӹ� �߿��� not available)
public:
	// ĳ���Ϳ� �����Ǵ� ���̺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCableComponent* Cable;

	// Hook�� ������ ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AActor* HookHand;

// CSM �ӹ� ���࿡ �ʿ��� �޼���
public:
	// ���� �۾� Hook�� ����� ������ ���͸� ���. �Ļ� BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void RegisterHookHand();

	// ������ ���ܷ� �̵�
	UFUNCTION(BlueprintCallable)
		void StartEVA();

	// ������ ������ �̵�
	UFUNCTION(BlueprintCallable)
		void ReturnIVA();

	// Grip ���� �� BP_AstronautCharacterVR���� ȣ��
	UFUNCTION(BlueprintCallable)
		void OnGrip(AActor* HandActor, bool bIsLeft);

	// Grip�� �� �� BP_AstronautCharacterVR���� ȣ��
	UFUNCTION(BlueprintCallable)
		void ReleaseGrip(AActor* HandActor, bool bIsLeft);

	// ���� �۾� �� Hook�� ����
	UFUNCTION(BlueprintCallable)
		void ControlHook();

// CSM ���� �۾��� �̵��� ����ϴ� �ۺ� �ʵ�
public:
	// ���� �۾� Grip�� ���� �ݰ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAGripRadius;

	// ���� �۾� OnGrip �� �̵� �ӵ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPullingForceMultiplier;

	// ���� �۾� ReleaseGrip �� �̵� �ӵ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPushingForceMultiplier;

// CSM ���� �۾��� �⵿�� ����ϴ� �ۺ� �ʵ�
public:
	// ���� �۾� �� ĳ���� CapsuleComponent ���� (�ݸ��� ���� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVACharacterHeight;

	// ���� �۾� �� ĳ���� Pitch ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVACharacterPitch;

	// ���� �۾� Grip�� ���� �ݰ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVAGripRadius;

	// ���� �۾� OnGrip �� �̵� �ӵ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVAPullingForceMultiplier;

	// ���� �۾� Grip�� ��� �� �� �߻��ϴ� �ܷ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVAExternalForceMagnitude;

	// ���� �۾����� �������� �̿��� �����ϴ� �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVAHookForce;

	// ���� �۾� ���̺� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVACableMaxLength;

private:
	// �޼� �� ������ Ȧ�� ����
	bool bIsGrabbingL, bIsGrabbingR;
	
	// �޼� �� ������ �ֱ� Ȧ�� ���� (AstronautCharacter�� ���� �� ������Ʈ�� Relative Location���� ����)
	FVector RecentGrabbingPointL, RecentGrabbingPointR;

	// �ֱ� ���� ���̺� ���� ����
	FVector RecentHookPoint;

	// ���� �۾� �� 1/120�ʸ��� ����Ǿ�, ���̺��� ���̰� �ʹ� ������� �ܷ��� ���� 
	void EVACableChecker();
	FTimerHandle TimerHandler;

	// ���̺��� ���̸� ��ȯ�ϴ� �Լ�. ���Ǹ� ���� ����
	float GetCableLength();
};