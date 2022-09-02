// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Fire.generated.h"

/*
 - Name        : AFire
 - Descirption : FireHose의 물에 닿으면 꺼지는 불 액터
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

	//Steam(불 진압 시 나오는 수증기)의 Opacity 값 조절을 위한 동적 머티리얼을 생성
	UFUNCTION()
		void InitSteamDynamicMaterial();

	//Emmiter의 크기를 업데이트한다
	UFUNCTION()
		void UpdateEmitterScale(class UParticleSystemComponent* Target, const float Variance);

	//Steam의 투명도를 업데이트 한다
	UFUNCTION()
		void UpdateSteamOpacity();

	//FireHose의 NS_Emiiter가 Apply하는 데미지를 받는다. FireScaleSize를 DamageAmount 만큼 줄임
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	//수증기가 사라지는 Timer를 설정하여 소멸을 시뮬레이션
	UFUNCTION()
		void SetSteamDisappearTimer();

	//Destroy할 준비가 되었다면, Destroy를 시도 (수증기가 모두 사라지면 Destroy)
	UFUNCTION()
		void TryDestroyFire();

	//불이 꺼졌는지 확인하고 꺼졌을 시의 로직을 실행 (콜리전, Destroy 처리 등)
	UFUNCTION()
		bool CheckAndUpdateSuppressedState();

	UFUNCTION(BlueprintPure)
		bool GetIsFireSuppressed() { return bIsFireSuppressed; }

	//불이 꺼지면 바인딩된 미션을 업데이트 한다 
	UFUNCTION()
		void UpdateMissionDelegate(int32 PlayerIdx, int32 TargetMissionID, int32 NewCondition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//미션 ID. 해당 값을 기반으로 미션 업데이트 델리게이트 호출
	UPROPERTY(EditAnywhere, Category = "Mission")
		int32 MissionID;

	//수증기의 초기 Opacity 값
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float SteamEmitterInitialOpacity = 1.0f; 

	//수증기가 소멸할때까지 걸리는 시간
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		float SteamEmitterLifeSpan = 100.0f;

	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	//불 이미터
	UPROPERTY(EditAnywhere, Category = "VFX")
		class UParticleSystemComponent* FireEmitter;

	//연기 효과 이미터 (화재 진압 로직 시)
	UPROPERTY(EditAnywhere, Category = "VFX")
		class UParticleSystemComponent* SteamEmitter;

	//연기 이미터 원본 머티리얼 
	UPROPERTY(EditAnywhere, Category = "VFX")
		class UMaterialInterface* SteamMaterialInterface; 

	//연기 이미터  Opacity 조절을 위한 다이나믹 머티리얼
	UPROPERTY()
		class UMaterialInstanceDynamic* SteamDynamicMaterial; 

	//불에 가까이 가지 못하게 하는 콜리전 볼륨
	UPROPERTY(EditAnywhere)
		USphereComponent* BlockingVolume;

	//불 경계를 나타내는 스태틱 메시
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* FireGuideMesh;

private:
	//게임모드 레퍼런스
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef;

	//이미터 업데이트 타이머 핸들
	UPROPERTY()
		FTimerHandle EmitterUpdateTimerHandle;

	//이미터 제거 타이머 핸들
	UPROPERTY()
		FTimerHandle DestroyTimerHandle;

	//Smoke의 최대 스케일
	UPROPERTY()
		float SmokeMaxScale = 5.0f;

	//불 이미터의 크기 (범위 : 0<=size<=1)
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float FireScaleSize = 1.0f;   

	//수증기 이미터의 크기
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float SteamScaleSize = 0.0f;   

	//수증기 이미터의 Opacity
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float SteamOpacityValue;

	//연기의 Life (특정 시간만큼 Opacity 업데이트)
	UPROPERTY()
		float SteamLifeSpan = 100.0f; 

	//Fire 액터를 Destroy를 할 준비가 되어있는지 판단
	UPROPERTY()
		bool bIsReadyToDestroy = false; 

	//불이 진압이 되었는지?
	UPROPERTY()
		bool bIsFireSuppressed;
};