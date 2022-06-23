// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Fire.generated.h"


/*
 - Name        : AFire
 - Descirption : FireHose�� ���� ������ ������ �� ����
 - Date        : 2022/06/22 LJH
*/


UCLASS(Category = "FireFighter")
class LISTENSERVERSTUDY_API AFire : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFire();

private:
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
		UParticleSystemComponent * FireEmitter; //�� �̹���
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float FireScaleSize = 1.0f;   //���� ũ�� (���� : 0<=size<=1)

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//FireHose�� NS_Emiiter�� Apply�ϴ� �������� �޴´�. FireScaleSize�� DamageAmount ��ŭ ����.
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

};
