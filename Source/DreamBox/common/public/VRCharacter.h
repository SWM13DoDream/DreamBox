// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "TransitionStructBase.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

/*
 - Name        : AVRCharacter
 - Descirption : ���� Playable VR ĳ���� Base
 - Date        : 2022/10/04 LJH
*/

UENUM(BlueprintType)
enum class EPlayerLevelSequenceType : uint8
{
	E_CrossFade	= 0		UMETA(DisplayName = "CrossFade"),
	E_FadeIn			UMETA(DisplayName = "FadeIn"),
	E_FadeOut			UMETA(DisplayName = "FadeOut")
};

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

///============================================
/// Replication, RPC ���� �Լ�
///============================================
public:	
	UFUNCTION(Client, Reliable)
		void OnRPCSetupContent(int32 PlayerID, FContentStartInfo StartInfo);
	
	//UFUNCTION(Client, Reliable)
		virtual void OnRPCStartContent(int32 PlayerID);
	
	UFUNCTION(Server, Reliable)
		virtual void MakeRPCInitPlayerTransform(FTransform InitialTransform);

	UFUNCTION(NetMulticast, Reliable)
		virtual void OnRPCInitPlayerTransform(FTransform InitialTransform);

///============================================
/// �⺻���� Movement ���� �Լ�
///============================================
public:
	//�⺻ �̵� �Լ� : �յ� �̵�
	UFUNCTION()
		virtual void MoveForward(float Value);

	//�⺻ �̵� �Լ� : �翷 �̵�
	UFUNCTION()
		virtual void MoveRight(float Value);

	//�⺻ ȸ�� �Լ� : 45�� ��ŭ ī�޶� ��ȯ
	UFUNCTION()
		virtual void SnapTurn(float Value);

	//SnapTurn�� �������� �ԷµǴ� ���� �����ϴ� �Լ�
	UFUNCTION()
		void ResetSnapTurnControllerInput();

	//Jump�� Ȱ��ȭ/��Ȱ��ȭ ��
	UFUNCTION()
		void SetCanJump(bool NewState);

///============================================
/// Level Sequence / Level Streaming ���� �Լ�
///============================================
public:	
	UFUNCTION(Client, Reliable)
		void PlayLevelInitSequence();

	//ũ�ν� ���̵带 ������ ����ϴ� ����, �� �ڽ� ���Ӹ�� Ŭ�������� ���ε� �ؾ���
	//PlayerID �̻�� �Ķ���� ���� ����
	UFUNCTION(BlueprintCallable)
		float PlayLevelSequence(EPlayerLevelSequenceType TargetSequenceType);

	UFUNCTION()
		virtual void InitLevelSequence();

	//���Ӹ�� ���۷��� �ʱ�ȭ
	UFUNCTION()
		void InitGameModeRef();

	//���� ��ũ��Ʈ ���۷����� �ʱ�ȭ
	UFUNCTION()
		void InitLevelScriptRef();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		class APersistentLevelBase* GetLevelScriptRef() { return LevelScriptRef; }

	//���� ������ �ּҸ� ��ȯ
	UFUNCTION(BlueprintCallable)
		FString GetCurrentIpAddress();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

///============================================
/// ������Ʈ  ���
///============================================
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

///============================================
/// ��������Ʈ ���
///============================================
public:
	//���� ������ �迭 (0 : CrossFade, 1 : FadeIn, 2 : FadeOut)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		TArray<class ULevelSequence*> LevelSequenceList;

	//���� ������ ���� �迭 (MUST BE ADDED)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		TArray<float> LevelSequenceLengthList; 

	//C++ ������ ��� ���� Ÿ�̸� �ڵ� 
	UPROPERTY()
		struct FTimerHandle WaitHandle;

	//������ ��������? (BP���� �ɼ� ����, �⺻�� : t)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
		bool bCanJump = true; 

///============================================
/// private ���
///============================================
private:
	//SnapTurn ������ ��������? (���� �Է� ����)
	UPROPERTY()
		bool bSnapTurnIsFinished;

	UPROPERTY()
		int32 PlayerControllerID;

	//������ �÷��̾� (FadeIn & Out)
	UPROPERTY()
		TArray<class ULevelSequencePlayer*> LevelSequencePlayerList;

	UPROPERTY()
		class ADreamBoxGameModeBase* GamemodeRef;

	UPROPERTY()
		class APersistentLevelBase* LevelScriptRef;

};
