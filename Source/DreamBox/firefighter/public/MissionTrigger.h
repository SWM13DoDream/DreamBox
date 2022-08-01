// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirefighterGamemode.h"
#include "Components/BoxComponent.h"
#include "MissionTrigger.generated.h"

UCLASS()
class DREAMBOX_API AMissionTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissionTrigger();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor
							, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void UpdateMissionDelegate();

	UFUNCTION()
		void UpdateMissionTriggerCollision(int32 PlayerId, int32 RemoveMissionId, int32 NewCondition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//�� Ʈ���� ������ �Ҵ�� �̼� ID 
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 MissionID = 0;

	//�ʱ� �ݸ��� �ɼ� ���� (Initial �̼��� ��� �ʹݺ��� Overlap)
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsRequirePrevMission = false;

	//�� Ʈ���� ������ Ȱ��ȭ(BlockAll -> OverlapAll) �ϱ� ���� �̸� �Ϸ� ���Ѿ� �� �̼ǵ�
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 PrevMissionID = -1;

	//�ڵ����� �̼��� Ȱ��ȭ �� ������ ����
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsAutoActivate = false;

	//�Ҵ�� �̼�ID�� ������� ���� ��������Ʈ�� ȣ���� ������?
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsRemoveVolume = false;

	//��Ʈ ������Ʈ
	UPROPERTY(EditAnywhere)
		USceneComponent* DefaultSceneRoot;

	//�÷��̾��� ���������� �̺�Ʈ�� Ʈ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* TriggerVolume;

private:
	UPROPERTY()
		AFirefighterGamemode* GamemodeRef;
};
