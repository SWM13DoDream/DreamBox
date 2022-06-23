// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceExport.h"
#include "Components/ChildActorComponent.h"
#include "FireHose.generated.h"

/*
 - Name        : AFireHose
 - Descirption : 물을 뿜는 소방호스 액터
 - Date        : 2022/06/22 LJH
*/

UCLASS(Category="FireFighter")
class LISTENSERVERSTUDY_API AFireHose : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireHose();
	
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	//소방호스의 물 이미터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")	
		UNiagaraComponent* WaterEmitter;				 
	
	//Hose의 메인 StaticMesh
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		UChildActorComponent * HoseMesh; 
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
