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

	// VR ĳ���� �̵� ������
		void MoveForward(float Value) override;

	// VR ĳ���� �̵� ������
		void MoveRight(float Value) override;

	// ���ͷ��� Ű Press�� ���ε�
	UFUNCTION()
		void OnInteract();

	// ���ͷ��� Ű Release�� ���ε�
	UFUNCTION()
		void ReleaseInteract();

protected:
	// ���� ���ֺ���� ������ ������ �Ʒ� ��Ƽ�÷��� ���� �Լ����� Client RPC�� ���ǵǾ� ����.
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

	// �̼Ƿ���-����Ʈ �߰� ���� ��Ʈ�ѷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		class AGamemodeArbiter* Arbiter;

public:
	// Ư�� Ű (Meta Quest 2 - R��Ʈ�ѷ� AŰ) �Է� �Լ�
	UFUNCTION(BlueprintCallable)
		void OnSpecialKey();

	UFUNCTION(BlueprintCallable)
		void ReleaseSpecialKey();

/* �ӹ� ���� ���� ���� �޼���. ����&�������� ����ϴ� ��쿡�� �Ļ� BP�� ���� */
public:
	// �߰��� ���. BeginPlay�� ���ÿ� ���� �� GamemodeArbiter�κ��� ȣ��
	UFUNCTION(BlueprintCallable)
		void RegisterArbiter(class AGamemodeArbiter* Invoker);

	// ���� ������ ���. ���� ��� PostLogin ������ RPC�� ȣ��� �Լ����� �Բ� ȣ���
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "PreMission")
		void PlayInitialSequence();

	// �÷��̾� ��� ���� �� �ٸ� �÷��̾� ���� �� ��� ����
	UFUNCTION(BlueprintCallable)
		void CloseWaitingPanel();

	// �̼� ���� ���� �г� ���� (Arbiter ���)
	UFUNCTION(BlueprintCallable)
		void OpenSelectMissionPanel();

	// �̼� ���� �� �ܺ� �������κ��� ȣ��
	UFUNCTION(BlueprintCallable)
		void SelectMission(int32 Mission);

	// �̼� ���� â -> �̼� ���� ��ġ�� �ڿ������� �̵��� ���� ������ ����
	UFUNCTION(BlueprintImplementableEvent, Category = "PreMission")
		void PlayMissionInitSequence();

	// �ӹ� ����. PlayMissionInitSequence�� ���� ȣ��
	UFUNCTION(BlueprintCallable)
		void InitializeMission();

	// ���� ���� ����. FName �Ķ���Ϳ� ���� �ٸ� ������ �����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void OpenInfoWidget(const FName& Key);

	// ���� ���� �ݱ�. ���� FName �Ķ���Ϳ� ���� �ٸ� ������ �����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void CloseInfoWidget(const FName& Key);

	// Ư�� ��� �Լ�: �������� ȣ���Ͽ� ȭ�� ũ�ν����̵�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void PlayCrossFade();

/* �ӹ� ���� ���� ������Ʈ */
public:
	// ĳ���� ī�޶� �����Ǵ� �߿� �ȳ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* InfoWidget;

	// ĳ���� ī�޶� �����Ǵ� ���̾�α� ��Ʈ�ѷ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* DialogController;

/* �ӹ� ���� ���� ���� ���� (�̼� ���� ������ ��κ� LEM������ ���) */
public:
	// bool Ÿ������ ���� �̼� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsMissionDone;

	// TArray<bool> Ÿ������ ���� �̼� ���� (Expected Length = 6)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<bool> bIsSubmissionDone;

	// TArray<int> Ÿ������ �������� ���õ� ���� �̼� ���� (Expected Length = 3)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> RandomSubmissionIndices;

	// Text Ÿ���� ���� �̼� ���� ǥ�ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText MainMissionText;

	// TArray<FText> Ÿ���� ���� �̼� ���� ǥ�ð� (Max Length = 3)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FText> SubMissionText;

	// �÷��̾ �����̰ų� ��Ÿ �ൿ�� �� �� �ִ��� ���θ� ����.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bMovable;

	// Ÿ�̸ӿ� ǥ�õǴ� �ð��� ����. TIME_PERIOD�� ��ɼ��� �����ϴ� �� �ֱ⸦ ��Ÿ�� (���� ����: 5��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Time;

/* LEM �ӹ� ���� ���� ������Ʈ(CSM �ӹ� �߿��� not available) */
public:
	// ĳ���� VR Origin�� �����Ǵ� Ÿ�̸� ǥ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* TimerWidget;

	// ĳ���� VR Origin�� �����Ǵ� �̼� ǥ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionWidget;

private:
	// Ÿ�̸� ���� ��Ʈ�ѷ� (Ž�缱 �ӹ� InitializeMissions���� �ʱ�ȭ)
	class UTimerWidget* TimerController;

	// �̼� ���� ��Ʈ�ѷ� (Ž�缱 �ӹ� InitializeMissions���� �ʱ�ȭ)
	class UMissionWidget* MissionController;

	// 1�ʸ��� ����Ǵ� Ÿ�̸� �ڵ鷯
	void MissionTick();
	FTimerHandle MissionTickHandler;

/* LEM �ӹ� ���� �̼� ���� �޼��� */
public:
	// Ž�缱 ���� �ӹ� �Ϸ�
	UFUNCTION(BlueprintCallable)
		void DoMainMission();

	// Ž�缱 ���� �ӹ� �Ϸ�
	UFUNCTION(BlueprintCallable)
		void DoSubMission(int32 Index);

	// Ž�缱 �ܳ��� �̵��� ���� ĳ���� ��ġ ����
	UFUNCTION(BlueprintCallable)
		void MoveLEM(bool bIsEntering);

	// Ž�缱 �ӹ��� ����� �� �ִ��� üũ (Time���� üũ)
	UFUNCTION(BlueprintCallable)
		bool IsAboardable();

/* CSM �ӹ� ���� ���� ������Ʈ (LEM �ӹ� �߿��� not available) */
public:
	// ĳ���Ϳ� �����Ǵ� ���̺�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCableComponent* Cable;

	// Hook�� ������ ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AActor* HookHand;

/* CSM �ӹ� ���࿡ �ʿ��� �޼��� */
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

/* CSM ���� �۾��� �̵��� ����ϴ� �ۺ� �ʵ� */
public:
	// ���� �۾� Grip�� ���� �ݰ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAGripRadius;

	// ���� �۾� OnGrip �� �̵� �ӵ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPullingForceMultiplier;

	// ���� �۾� OnGrip �� �ӵ� ���� �Ⱓ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		int32 IVAPullingForceDecrementInterval;

	// ���� �۾� ReleaseGrip �� �̵� �ӵ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPushingForceMultiplier;

/* CSM ���� �۾��� �⵿�� ����ϴ� �ۺ� �ʵ� */
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

	// ���� �۾� OnGrip �� �ӵ� ���� �Ⱓ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		int32 EVAPullingForceDecrementInterval;

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

	// �ֱ� pulling force ���� (������ �ӵ� ���ҿ� �ʿ�)
	FVector RecentPullingForce;

	// Pulling Force ���� ī����
	int32 PullingForceDecrementCounter;

	// �ֱ� ���� ���̺� ���� ����
	FVector RecentHookPoint;

	// ��ɼ� �ӹ� �� 1/120�ʸ��� ����Ǿ�, ĳ���Ϳ��� �����ϴ� ���� ������ üũ
	void ForceChecker();
	FTimerHandle ForceCheckHandler;

	// ���̺��� ���̸� ��ȯ�ϴ� �Լ�. ���Ǹ� ���� ����
	float GetCableLength();

// ======================================= //
// ������ʹ� ���� ���� ������Ƽ�� �Լ��Դϴ�. //
// ======================================= //

public:
	// ������ ���� �Լ�. ���� ���κ��� ȣ��
	UFUNCTION(Client, Reliable)
		void OnRPCStartContent();

	// �̼��� �����Ͽ� ���� ��忡 ���, �ٸ� Ŭ���̾�Ʈ�� ���� OnRPCCheckReadyState ȣ��
	// ���� �ٸ� Ŭ���̾�Ʈ�� ���� �������� ���� ���¸� �̼� Lock ó��
	// �ٸ� Ŭ���̾�Ʈ�� �̼��� ������ ���¸� �ش� Ŭ���̾�Ʈ������ �̼� ����
	UFUNCTION(Server, Reliable)
		void MakeRPCSelectMission(int32 Mission);

	// �� MakeRPCSelectMission���κ��� ȣ��. ���� ��忡 ������ �� ������ ����
	UFUNCTION(Client, Reliable)
		void OnRPCCheckReadyState(bool bStartMission, int32 MissionToLock);

private:
	bool bIsWaitingPlayer;
};