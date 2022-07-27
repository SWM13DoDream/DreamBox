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
 - Description : ���� �մ� �ҹ�ȣ�� ����
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
	
	//�� �̹��͸� Ȱ��ȭ
	UFUNCTION()
		void ActivateEmitter();

	//�� �̹��͸� ��Ȱ��ȭ
	UFUNCTION()
		void DeactivateEmitter();

	//�ҹ�ȣ�� �� ���� ����Ʈ ������ ������Ʈ
	UFUNCTION()
		void UpdateSoundVolume(float NewVolume);

public: /*Replication ���� �Լ�*/
	//�Ұ� ������ Emitter�� Scale�� ������Ʈ(ȭ������ ����) - (Ŭ���̾�Ʈ���� ����)
	UFUNCTION(BlueprintCallable, NetMulticast, reliable)//NetMulticast, Reliable)
		void MulticastApplyDamageToFire(FVector Location);

	//�Ұ� ������ Emitter�� Scale�� ������Ʈ(ȭ������ ����) - (�������� ����)
	UFUNCTION(BlueprintCallable, Server, reliable)
		void ServerRPCApplyDamageToFire(FVector Location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: /*Component�� BP ���� ����*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		float FireHoseDamage;

	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	//�ҹ�ȣ���� �� �̹���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
		UNiagaraComponent* WaterEmitter;

	//Hose�� ���� StaticMesh
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		UChildActorComponent* HoseMesh;

	//Firehose�� ���� ����Ʈ
	UPROPERTY(EditAnywhere, Category = "Sound")
		UAudioComponent* FirehoseSound; 

private:
	//���� ����Ʈ ���� ���
	UPROPERTY()
		float SoundVolumeMultipiler = 1.0f;
};
