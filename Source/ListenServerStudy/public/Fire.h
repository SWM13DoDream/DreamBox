// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Fire.generated.h"


/*
 - Name        : AFire
 - Descirption : FireHose의 물에 닿으면 꺼지는 불 액터
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
		UParticleSystemComponent * FireEmitter; //불 이미터
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay")
		float FireScaleSize = 1.0f;   //불의 크기 (범위 : 0<=size<=1)

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//FireHose의 NS_Emiiter가 Apply하는 데미지를 받는다. FireScaleSize를 DamageAmount 만큼 줄임.
	UFUNCTION()
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

};
