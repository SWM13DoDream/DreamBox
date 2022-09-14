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

// LEM �ӹ� ���� ���� ������Ʈ (CSM �ӹ� �߿��� not available)  
public:
	// ĳ���� VR Origin�� �����Ǵ� Ÿ�̸� ǥ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* TimerWidget;

	// ĳ���� VR Origin�� �����Ǵ� �̼� ǥ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionWidget;

// CSM ���� �۾��� �̵��� ����ϴ� �޼��� �� �ʵ�
public:
	// Grip ���� �� BP_AstronautCharacterVR���� ȣ��
	UFUNCTION(BlueprintCallable)
		void OnGrip(AActor* HandActor, bool bIsLeft);

	// Grip�� �� �� BP_AstronautCharacterVR���� ȣ��
	UFUNCTION(BlueprintCallable)
		void ReleaseGrip(AActor* HandActor, bool bIsLeft);

	// ���� �۾� Grip�� ���� �ݰ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAGripRadius;

	// ���� �۾� OnGrip �� ���� �ۿ��ϱ� ���� �ּ� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPullingForceDistanceThreshold;

	// ���� �۾� OnGrip �� �̵� �ӵ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPullingForceMultiplier;

	// ���� �۾� ReleaseGrip �� �̵� �ӵ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPushingForceMultiplier;

private:
	// �޼� �� ������ Ȧ�� ����
	bool bIsGrabbingL, bIsGrabbingR;
	
	// �޼� �� ������ �ֱ� Ȧ�� ���� (AstronautCharacter�� ���� �� ������Ʈ�� Relative Location���� ����)
	FVector RecentGrabbingPointL, RecentGrabbingPointR;
};