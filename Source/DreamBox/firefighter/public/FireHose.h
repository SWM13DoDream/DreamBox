// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "FireHose.generated.h"

/*
 - Name        : AFireHose
 - Description : 물을 뿜는 소방호스 액터
 - Date        : 2022/09/02 LJH
*/

UCLASS(Category="Firefighter")
class DREAMBOX_API AFireHose : public AActor
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: /*Component와 BP 접근 변수*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		float FireHoseDamage;

	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	//소방호스의 물 이미터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		class UNiagaraComponent* WaterEmitter;

	//Hose의 메인 StaticMesh
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		UChildActorComponent* HoseMesh;

	//Firehose의 사운드 이펙트
	UPROPERTY(EditAnywhere, Category = "Sound")
		class UAudioComponent* FirehoseSound; 

private:
	//사운드 이펙트 볼륨 배수
	UPROPERTY()
		float SoundVolumeMultipiler = 1.0f;
};
