// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "TimerManager.h"
#include "FirefighterGamemode.h."
#include "FirefighterCharacter.h"
#include "GameFramework/Actor.h"
#include "RescueGoal.generated.h"

/*
 - Name        : ARescueGoal
 - Description : �����ǰ� �ִ� ĳ���͸� �������� ����Ʈ�� ��Ÿ����, ���� ���� �̺�Ʈ�� ȣ���ϴ� ����
 - Date        : 2022/07/20 LJH
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//���� ���� ����Ʈ�� ��Ÿ���� �ݸ��� ����. ������ �� ���� ���� �̺�Ʈ ȣ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* EventTrigger;

	//���ε��� �̼��� ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission")
		int32 MissionID;

	//�����ؾ��� �ο� ��
	UPROPERTY(EditAnywhere, Category = "Mission")
		int32 TargetRescueCount; 

private:
	//������� ������ �ο� ��
	UPROPERTY()
		int32 CurrentRescueCount;

	//���Ӹ�� ���۷���
	UPROPERTY()
		AFirefighterGamemode* GamemodeRef;

	//�÷��̾� ĳ���� ���۷���
	UPROPERTY()
		AFirefighterCharacter* FirefighterCharacterRef;

	//C++ ������ ��� ���� Ÿ�̸� �ڵ� : �̻��
	UPROPERTY()
		FTimerHandle WaitHandle;
};
