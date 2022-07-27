// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceExport.h"
#include "Components/ChildActorComponent.h"
#include "Components/AudioComponent.h"
#include "FireHose.generated.h"

/*
 - Name        : AFireHose
 - Description : 물을 뿜는 소방호스 액터
 - Date        : 2022/07/22 LJH
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

	//소방호스 물 사운드 이펙트 볼륨을 업데이트
	UFUNCTION()
		void UpdateSoundVolume(float NewVolume);

public: /*Replication 관련 함수*/
	//불과 수증기 Emitter의 Scale을 업데이트(화재진압 로직) - (클라이언트에서 실행)
	UFUNCTION(BlueprintCallable, NetMulticast, reliable)//NetMulticast, Reliable)
		void MulticastApplyDamageToFire(FVector Location);

	//불과 수증기 Emitter의 Scale을 업데이트(화재진압 로직) - (서버에서 실행)
	UFUNCTION(BlueprintCallable, Server, reliable)
		void ServerRPCApplyDamageToFire(FVector Location);

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
		UNiagaraComponent* WaterEmitter;

	//Hose의 메인 StaticMesh
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		UChildActorComponent* HoseMesh;

	//Firehose의 사운드 이펙트
	UPROPERTY(EditAnywhere, Category = "Sound")
		UAudioComponent* FirehoseSound; 

private:
	//사운드 이펙트 볼륨 배수
	UPROPERTY()
		float SoundVolumeMultipiler = 1.0f;
};
