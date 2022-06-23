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
 - Descirption : ���� �մ� �ҹ�ȣ�� ����
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

	//�ҹ�ȣ���� �� �̹���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")	
		UNiagaraComponent* WaterEmitter;				 
	
	//Hose�� ���� StaticMesh
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		UChildActorComponent * HoseMesh; 
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
