// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Fire.generated.h"

/*
 - Name        : AFire
 - Descirption : FireHose�� ���� ������ ������ �� ����
 - Date        : 2022/09/02 LJH
*/

UCLASS(Category = "Firefighter")
class DREAMBOX_API AFire : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFire();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Steam(�� ���� �� ������ ������)�� Opacity �� ������ ���� ���� ��Ƽ������ ����
	UFUNCTION()
		void InitSteamDynamicMaterial();

	//Emmiter�� ũ�⸦ ������Ʈ�Ѵ�
	UFUNCTION()
		void UpdateEmitterScale(class UParticleSystemComponent* Target, const float Variance);

	//Steam�� ������ ������Ʈ �Ѵ�
	UFUNCTION()
		void UpdateSteamOpacity();

	//FireHose�� NS_Emiiter�� Apply�ϴ� �������� �޴´�. FireScaleSize�� DamageAmount ��ŭ ����
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	//�����Ⱑ ������� Timer�� �����Ͽ� �Ҹ��� �ùķ��̼�
	UFUNCTION()
		void SetSteamDisappearTimer();

	//Destroy�� �غ� �Ǿ��ٸ�, Destroy�� �õ� (�����Ⱑ ��� ������� Destroy)
	UFUNCTION()
		void TryDestroyFire();

	//���� �������� Ȯ���ϰ� ������ ���� ������ ���� (�ݸ���, Destroy ó�� ��)
	UFUNCTION()
		bool CheckAndUpdateSuppressedState();

	UFUNCTION(BlueprintPure)
		bool GetIsFireSuppressed() { return bIsFireSuppressed; }

	//���� ������ ���ε��� �̼��� ������Ʈ �Ѵ� 
	UFUNCTION()
		void UpdateMissionDelegate(int32 PlayerIdx, int32 TargetMissionID, int32 NewCondition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//�̼� ID. �ش� ���� ������� �̼� ������Ʈ ��������Ʈ ȣ��
	UPROPERTY(EditAnywhere, Category = "Mission")
		int32 MissionID;

	//�������� �ʱ� Opacity ��
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float SteamEmitterInitialOpacity = 1.0f; 

	//�����Ⱑ �Ҹ��Ҷ����� �ɸ��� �ð�
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float SteamEmitterLifeSpan = 100.0f;

	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	//�� �̹���
	UPROPERTY(EditAnywhere, Category = "VFX")
		class UParticleSystemComponent* FireEmitter;

	//���� ȿ�� �̹��� (ȭ�� ���� ���� ��)
	UPROPERTY(EditAnywhere, Category = "VFX")
		class UParticleSystemComponent* SteamEmitter;

	//���� �̹��� ���� ��Ƽ���� 
	UPROPERTY(EditAnywhere, Category = "VFX")
		class UMaterialInterface* SteamMaterialInterface; 

	//���� �̹���  Opacity ������ ���� ���̳��� ��Ƽ����
	UPROPERTY()
		class UMaterialInstanceDynamic* SteamDynamicMaterial; 

	//�ҿ� ������ ���� ���ϰ� �ϴ� �ݸ��� ����
	UPROPERTY(EditAnywhere)
		USphereComponent* BlockingVolume;

	//�� ��踦 ��Ÿ���� ����ƽ �޽�
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* FireGuideMesh;

private:
	//���Ӹ�� ���۷���
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef;

	//�̹��� ������Ʈ Ÿ�̸� �ڵ�
	UPROPERTY()
		FTimerHandle EmitterUpdateTimerHandle;

	//�̹��� ���� Ÿ�̸� �ڵ�
	UPROPERTY()
		FTimerHandle DestroyTimerHandle;

	//Smoke�� �ִ� ������
	UPROPERTY()
		float SmokeMaxScale = 5.0f;

	//�� �̹����� ũ�� (���� : 0<=size<=1)
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float FireScaleSize = 1.0f;   

	//������ �̹����� ũ��
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float SteamScaleSize = 0.0f;   

	//������ �̹����� Opacity
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float SteamOpacityValue;

	//������ Life (Ư�� �ð���ŭ Opacity ������Ʈ)
	UPROPERTY()
		float SteamLifeSpan = 100.0f; 

	//Fire ���͸� Destroy�� �� �غ� �Ǿ��ִ��� �Ǵ�
	UPROPERTY()
		bool bIsReadyToDestroy = false; 

	//���� ������ �Ǿ�����?
	UPROPERTY()
		bool bIsFireSuppressed;
};