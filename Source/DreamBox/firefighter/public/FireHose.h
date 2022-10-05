// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "NiagaraDataInterfaceExport.h"
#include "FireHose.generated.h"

/*
 - Name        : AFireHose
 - Description : 물을 뿜는 소방호스 액터
 - Date        : 2022/10/01 LJH
*/

UCLASS(Category="Firefighter")
class DREAMBOX_API AFireHose : public AActor, public INiagaraParticleCallbackHandler
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireHose();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//물 이미터를 활성화
	UFUNCTION()
		void ActivateEmitter();

	//물 이미터를 비활성화
	UFUNCTION()
		void DeactivateEmitter();

	UFUNCTION(BlueprintCallable)
		void ApplyDamageToFire(FVector Location);

	UFUNCTION()
		virtual void ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: /*Component와 BP 접근 변수*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		float FireHoseDamage = 0.0003;

	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	//소방호스의 물 이미터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		class UNiagaraComponent* WaterEmitter;

	//소방호스 메인 스태틱 메시
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		UStaticMeshComponent* FireHoseMesh;

	//Firehose의 사운드 이펙트
	UPROPERTY(EditAnywhere, Category = "Sound")
		class UAudioComponent* FirehoseSound; 

private:
	//사운드 이펙트 볼륨 배수
	UPROPERTY()
		float SoundVolumeMultipiler = 1.0f;
};
