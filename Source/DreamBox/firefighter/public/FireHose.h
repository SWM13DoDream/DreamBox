// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "FireHose.generated.h"

/*
 - Name        : AFireHose
 - Description : ���� �մ� �ҹ�ȣ�� ����
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
	
	//�� �̹��͸� Ȱ��ȭ
	UFUNCTION()
		void ActivateEmitter();

	//�� �̹��͸� ��Ȱ��ȭ
	UFUNCTION()
		void DeactivateEmitter();

	UFUNCTION(BlueprintCallable)
		void ApplyDamageToFire(FVector Location);

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
		class UNiagaraComponent* WaterEmitter;

	//Hose�� ���� StaticMesh
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		UChildActorComponent* HoseMesh;

	//Firehose�� ���� ����Ʈ
	UPROPERTY(EditAnywhere, Category = "Sound")
		class UAudioComponent* FirehoseSound; 

private:
	//���� ����Ʈ ���� ���
	UPROPERTY()
		float SoundVolumeMultipiler = 1.0f;
};
