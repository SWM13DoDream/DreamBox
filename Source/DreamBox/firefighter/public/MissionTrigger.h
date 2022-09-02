// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "MissionTrigger.generated.h"

/*
 - Name        : AMissionTrigger
 - Description : Ư�� �̼��� �߰� & ������Ʈ & ����
                 �̼� Flow�� ������ ���� Ư�� ������ Block
 - Date        : 2022/09/01 LJH
*/

UCLASS()
class DREAMBOX_API AMissionTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissionTrigger();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�÷��̾ ������ �ȴٸ�, ID�� ���� �̼��� ������Ʈ
	UFUNCTION()
		void OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor
							, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//�̼� ��������Ʈ�� ȣ�� (����/�߰� �����Ͽ�)
	UFUNCTION()
		void UpdateMissionDelegate();

	//Ư�� �̼��� �߰� �Ǿ��� ���, ���ǿ� ���� �� ������ �ݸ��� ä���� overlapAll���� ������Ʈ
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
	//���Ӹ�� ���۷���
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef;
};
