// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Fire.generated.h"


/*
 - Name        : AFire
 - Descirption : FireHose의 물에 닿으면 꺼지는 불 액터
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

	//불과 수증기 Emitter의 Scale을 업데이트 (멀티캐스트)
	UFUNCTION(NetMulticast, reliable)//NetMulticast, Reliable)
		void MulticastUpdateEmitterScale(UParticleSystemComponent* Target, const FVector& NewScale);

	//불과 수증기 Emitter의 Scale을 업데이트 (서버에서 실행)
	UFUNCTION(Server, reliable)
		void ServerRPCUpdateEmitterScale(UParticleSystemComponent* Target, const FVector& NewScale);

	//Steam(불 진압 시 나오는 수증기)의 Opacity 값 조절을 위한 동적 머티리얼을 생성
	UFUNCTION()
		void InitSteamDynamicMaterial();

	//불이 꺼지고 수증기가 소멸하는 효과를 위해 Opacity값을 Update (멀티캐스트)
	UFUNCTION(NetMulticast, reliable)
		void MulticastUpdateSteamOpacity();

	//불이 꺼지고 수증기가 소멸하는 효과를 위해 Opacity값을 Update (서버에서 실행
	UFUNCTION(Server, reliable)
		void ServerRPCUpdateSteamOpacity(); 

	//FireHose의 NS_Emiiter가 Apply하는 데미지를 받는다. FireScaleSize를 DamageAmount 만큼 줄임
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	//수증기가 사라지는 Timer를 설정하여 소멸을 시뮬레이션
	UFUNCTION()
		void SetSteamDisappearTimer();

	//Destroy할 준비가 되었다면, Destroy를 시도 (수증기가 모두 사라지면 Destroy)
	UFUNCTION()
		void TryDestroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystemComponent* FireEmitter; //불 이미터

	UPROPERTY(EditAnywhere, Category = "VFX")
		UParticleSystemComponent* SteamEmitter; //연기 효과 이미터 (화재 진압 로직 시)

	UPROPERTY(EditAnywhere, Category = "VFX")
		UMaterialInterface* SteamMaterialInterface; //연기 이미터 원본 머티리얼 

	UPROPERTY()
		UMaterialInstanceDynamic* SteamDynamicMaterial; //연기 이미터  Opacity 조절을 위한 다이나믹 머티리얼

	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float FireScaleSize = 1.0f;   //불 이미터의 크기 (범위 : 0<=size<=1)

	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float SteamScaleSize = 0.0f;  //수증기 이미터의 크기 

	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float SteamOpacityValue = 1.0f; //수증기 이미터의 Opacity

	UPROPERTY()
		bool IsReadyToDestroy = false; 


};