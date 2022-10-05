// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautControllableInterface.h"
#include "GameFramework/Actor.h"
#include "GrabUserDisplay.generated.h"

/*
 - Name			: AGrabUserDisplay
 - Author		: DEVroar
 - Descirption	: ���ֺ���� CSM �ӹ����� Grip�� ����� �����ߴ��� Ȯ���ϴ� ���÷���
 - Date			: 2022/09/29
*/

UCLASS()
class DREAMBOX_API AGrabUserDisplay : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabUserDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Root Component ������ ���� �� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		USphereComponent* EmptyComponent;

	// Grip ������ ��Ÿ���� Animating Sphere ����ƽ �޽� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* SphereMesh;

	// Grip ���⸦ ��Ÿ���� ȭ��ǥ ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UArrowComponent* ForceArrow;

protected:
	// �ش� Grip�� �̿��ϰ� �ִ� actor ���۷���
	class AAstronautCharacter* PlayerActor;
	AActor* HandActor;
	bool bLeft;

	// Activate ���� Display ��ġ. Arrow Length ǥ���� ���
	FVector LocationWhenActivated;

	// 1�ʸ��� ����Ǵ� Ÿ�̸� �ڵ鷯
	void DisplayTick();
	FTimerHandle DisplayTickHandler;

public:
	// ������ �⺻ ��Ʈ�ѷ� ���͸� ��� (PlayerActor, HandActor)
	UFUNCTION(BlueprintCallable)
		void Initialize(AActor* Player, AActor* Hand, bool bIsLeft);

	// ���� Ȱ��ȭ
	void ActivateDisplay(bool bEnableArrow);

public:
	// �������̽����� ��ӹ��� �Լ� ����. GrabUserDisplay������ false�� �޾��� ���� ���� ���͸� ��Ȱ��ȭ
	virtual void SetStatus_Implementation(bool Value) override;

	// �������̽����� ��ӹ��� �Լ� ����
	virtual AActor* GetActor_Implementation() override;
};
