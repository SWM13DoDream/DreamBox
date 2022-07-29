// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirefighterGamemode.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Fire.generated.h"


/*
 - Name        : AFire
 - Descirption : FireHose�� ���� ������ ������ �� ����
 - Date        : 2022/07/20 LJH
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
		void UpdateEmitterScale(const float Variance);

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

	//���� ������ ���ε��� �̼��� ������Ʈ �Ѵ� 
	UFUNCTION()
		void UpdateMissionDelegate(int32 PlayerIdx, int32 TargetMissionID, int32 NewCondition);

public: //Replication ���� �Լ�
	//�Ұ� ������ Emitter�� Scale�� Value��ŭ ������Ʈ (��Ƽĳ��Ʈ)
	UFUNCTION(NetMulticast, reliable)//NetMulticast, Reliable)
		void MulticastUpdateEmitterScale(UParticleSystemComponent* Target, const float Variance);

	//�Ұ� ������ Emitter�� Scale�� Value��ŭ ������Ʈ (�������� ����)
	UFUNCTION(Server, reliable)
		void ServerRPCUpdateEmitterScale(UParticleSystemComponent* Target, const float Variance);

	//���� ������ �����Ⱑ �Ҹ��ϴ� ȿ���� ���� Opacity���� Update (��Ƽĳ��Ʈ)
	UFUNCTION(NetMulticast, reliable)
		void MulticastUpdateSteamOpacity();

	//���� ������ �����Ⱑ �Ҹ��ϴ� ȿ���� ���� Opacity���� Update (�������� ����
	UFUNCTION(Server, reliable)
		void ServerRPCUpdateSteamOpacity();

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
		UParticleSystemComponent* FireEmitter;

	//���� ȿ�� �̹��� (ȭ�� ���� ���� ��)
	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystemComponent* SteamEmitter;

	//���� �̹��� ���� ��Ƽ���� 
	UPROPERTY(EditAnywhere, Category = "VFX")
		UMaterialInterface* SteamMaterialInterface; 

	//���� �̹���  Opacity ������ ���� ���̳��� ��Ƽ����
	UPROPERTY()
		UMaterialInstanceDynamic* SteamDynamicMaterial; 

	UPROPERTY(EditAnywhere)
		USphereComponent* BlockingVolume;

private:
	//���Ӹ�� ���۷���
	UPROPERTY()
		AFirefighterGamemode* GamemodeRef;

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