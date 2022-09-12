// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautControllableInterface.h"
#include "AstronautDestinationGuide.generated.h"

UCLASS()
class DREAMBOX_API AAstronautDestinationGuide : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstronautDestinationGuide();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// ����ƽ �޽� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* CylinderMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* ConeMesh;

public:
	// Visibility ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void SetVisibility(bool Value);

public:
	// �������̽����� ��ӹ��� �Լ� ����. AstronautDestinationGuide������ Visibility ������ ����
	virtual void SetStatus_Implementation(bool Value) override;
};
