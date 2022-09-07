// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "StairPortal.generated.h"

/*
 - Name        : AStairPortal 
 - Description : ��� ��Ʈ�� ������ ���� �ڵ� �̵� ����
                 �⺻ ������ 1��->3��->2��->... ������,
				 Ư�� �̼��� �߰��� �� 1��->2��, 2��->3�� ���� 
				 ������ �����ϵ��� Ŀ������ �� �ִ�
 - Date        : 2022/09/04 LJH
*/

UCLASS()
class DREAMBOX_API AStairPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStairPortal();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void ActivatePortal(int32 PlayerID, int32 MissionID, int32 Variable);

	//�÷��̾ ������ �ȴٸ�, ID�� ���� �̼��� ������Ʈ
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	//��Ʈ ������Ʈ
	UPROPERTY()
		USceneComponent* DefaultSceneRoot;

	// �÷��̾��� ���������� �̺�Ʈ�� Ʈ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* TriggerVolume;

	//������ ��ġ�� ����
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<AStairPortal*> TeleportPointArray;

	//�⺻ ���� Ÿ�� ��ġ
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 DefaultDestination; 

	//Ư�� �̼��� ����� ���� ������ Ÿ�� ��ġ
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 MissionDestination = -1;

	//ù ��° �� ��Ż����?
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsFirstFloor = false;

	//���� ��ġ�� "MissionDestination"���� �ٲ� �̼�ID 
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 TargetMissionID;

private:
	//���Ӹ�� ���۷���
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef;

	UPROPERTY()
		ACharacter* PlayerCharacterRef;

	//C++ ������ ��� ���� Ÿ�̸� �ڵ� 
	UPROPERTY()
		struct FTimerHandle WaitHandle;
};
