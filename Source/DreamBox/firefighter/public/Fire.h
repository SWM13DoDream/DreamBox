// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Fire.generated.h"


/*
 - Name        : AFire
 - Descirption : FireHose�� ���� ������ ������ �� ����
 - Date        : 2022/06/26 LJH
*/

UCLASS(Category = "FireFighter")
class DREAMBOX_API AFire : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFire();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�Ұ� ������ Emitter�� Scale�� ������Ʈ (��Ƽĳ��Ʈ)
	UFUNCTION(NetMulticast, reliable)//NetMulticast, Reliable)
		void MulticastUpdateEmitterScale(UParticleSystemComponent* Target, const FVector& NewScale);

	//�Ұ� ������ Emitter�� Scale�� ������Ʈ (�������� ����)
	UFUNCTION(Server, reliable)
		void ServerRPCUpdateEmitterScale(UParticleSystemComponent* Target, const FVector& NewScale);

	//Steam(�� ���� �� ������ ������)�� Opacity �� ������ ���� ���� ��Ƽ������ ����
	UFUNCTION()
		void InitSteamDynamicMaterial();

	//���� ������ �����Ⱑ �Ҹ��ϴ� ȿ���� ���� Opacity���� Update (��Ƽĳ��Ʈ)
	UFUNCTION(NetMulticast, reliable)
		void MulticastUpdateSteamOpacity();

	//���� ������ �����Ⱑ �Ҹ��ϴ� ȿ���� ���� Opacity���� Update (�������� ����
	UFUNCTION(Server, reliable)
		void ServerRPCUpdateSteamOpacity(); 

	//FireHose�� NS_Emiiter�� Apply�ϴ� �������� �޴´�. FireScaleSize�� DamageAmount ��ŭ ����
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	//�����Ⱑ ������� Timer�� �����Ͽ� �Ҹ��� �ùķ��̼�
	UFUNCTION()
		void SetSteamDisappearTimer();

	//Destroy�� �غ� �Ǿ��ٸ�, Destroy�� �õ� (�����Ⱑ ��� ������� Destroy)
	UFUNCTION()
		void TryDestroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystemComponent* FireEmitter; //�� �̹���

	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystemComponent* SteamEmitter; //���� ȿ�� �̹��� (ȭ�� ���� ���� ��)

	UPROPERTY(EditAnywhere, Category = "VFX")
		UMaterialInterface* SteamMaterialInterface; //���� �̹��� ���� ��Ƽ���� 

	UPROPERTY()
		UMaterialInstanceDynamic* SteamDynamicMaterial; //���� �̹���  Opacity ������ ���� ���̳��� ��Ƽ����

	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float FireScaleSize = 1.0f;   //�� �̹����� ũ�� (���� : 0<=size<=1)

	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float SteamScaleSize = 0.0f;  //������ �̹����� ũ�� 

	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float SteamOpacityValue = 1.0f; //������ �̹����� Opacity

	UPROPERTY()
		bool IsReadyToDestroy = false; 


};