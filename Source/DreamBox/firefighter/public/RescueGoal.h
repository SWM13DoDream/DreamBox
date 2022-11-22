// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "RescueGoal.generated.h"

/*
 - Name        : ARescueGoal
 - Description : �����ǰ� �ִ� ĳ���͸� �������� ����Ʈ�� ��Ÿ����, ���� ���� �̺�Ʈ�� ȣ���ϴ� ����
 - Date   : 2022/09/27 LJH
*/

UCLASS()
class DREAMBOX_API ARescueGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARescueGoal();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�÷��̾ �ش� ����Ʈ�� �Դٸ�, TriggerRescurEvent ȣ��  
	UFUNCTION()
		void TriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void TryActivateActor(int32 PlayerId, int32 MissionId, int32 Variable);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateRescueMission(class AFirefighterCharacter* PlayerCharacterRef, class AInjuredCharacter* InjuredCharacterRef);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//�ֻ��� ��Ʈ ������Ʈ
	UPROPERTY()
		USceneComponent* DefaultSceneRoot;

	//���� ���� ����Ʈ�� ��Ÿ���� �ݸ��� ����. ������ �� ���� ���� �̺�Ʈ ȣ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* EventTrigger;
	
	//���� ���� ����Ʈ�� �ð������� �����ִ� ���̵� �޽� (���� �׵θ� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* DestinationGuideMesh;

	//���� ���� ����Ʈ�� �ð������� �����ִ� ���̵� �޽� (ȭ��ǥ)
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DestinationArrowMesh;

public:
	//�����ؾ��� �ο� ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission")
		int32 TargetRescueCount = 4; 

	UPROPERTY(EditAnywhere, Category = "Mission")
		TArray<int32> RescueMissionIdList;

private:
	//�÷��̾� ĳ���� ���۷���
	UPROPERTY()
		class AFirefighterCharacter* FirefighterCharacterRef;

	//C++ ������ ��� ���� Ÿ�̸� �ڵ� : �̻��
	UPROPERTY()
		struct FTimerHandle WaitHandle;

protected:
	//���Ӹ�� ���۷���
	UPROPERTY(BlueprintReadOnly)
		class AFirefighterGamemode* GamemodeRef;

	//������� ������ �ο� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentRescueCount = 0;

	//�̼� �̺�Ʈ�� ���� Ȱ��ȭ�� �Ǿ�����?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsActivated;
};
