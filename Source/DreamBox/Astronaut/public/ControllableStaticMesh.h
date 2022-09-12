// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautControllableInterface.h"
#include "ControllableStaticMesh.generated.h"

UCLASS()
class DREAMBOX_API AControllableStaticMesh : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AControllableStaticMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// ���Ӹ�� �̼� state�� ����Ǵ� ����ƽ �޽� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* DefaultMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* ActivatedMesh;

public:
	// bIsActivated ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void SetActivation(bool Value);

	// SetActivation(true)�� ȣ��� �� �߰������� BP���� ������ ������ �ִٸ� ȣ��
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void OnActivated();

public:
	// �������̽����� ��ӹ��� �Լ� ����. ControllableStaticMesh������ Activate ������ ����
	virtual void SetStatus_Implementation(bool Value) override;

private:
	// Ȱ��ȭ ���� ���� ����
	bool bIsActivated;
};
