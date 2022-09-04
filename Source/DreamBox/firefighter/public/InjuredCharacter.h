// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "InjuredCharacter.generated.h"

/*
 - Name        : AInjuredCharacter
 - Description : ĳ���Ͱ� ������ �䱸���� ĳ����
 - Date        : 2022/09/02 LJH
*/

UCLASS()
class DREAMBOX_API AInjuredCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInjuredCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�÷��̾ ������ ������ üũ. ������ �Դٸ�(���� ���� ���Դٸ�) Carry ���ͷ����� �����ϵ��� ������Ʈ
	UFUNCTION()
		void InteractionTriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp
								, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//�÷��̾ �ָ������� üũ. ���� ������ �����ٸ� Carry ���ͷ����� �Ұ����ϵ��� ������Ʈ
	UFUNCTION()
		void InteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor
								, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//ĳ���Ͱ� �÷��̾�� �����ִ� ���ȿ��� �ݸ����� �����Ѵ�. 
	UFUNCTION()
		void SetCharacterCollisionState(bool NewState);

	//�����ǰ� �ִ��� ������Ʈ (�ִϸ��̼� ������Ʈ ����)
	UFUNCTION()
		void SetIsBeingRescued(bool NewState);

	//�̼� �߰� �̺�Ʈ�� ���ε� �Ǿ, �Ҵ�� ID�� �´� �̼��� �߰��Ǹ� �� ���͸� Activate
	UFUNCTION()
		void TryActivateMissionActor(int TargetPlayerId, int NewMissionId, int32 Variable);

	/* --- Get/Set �Լ� ----- */
	UFUNCTION(BlueprintPure)
		bool GetIsBeingRescued() { return bIsBeingRescued; }
	
	UFUNCTION(BlueprintCallable)
		void SetIsRescued(bool NewState) { bIsRescued = NewState; }

	UFUNCTION(BlueprintCallable)
		bool GetIsRescued() { return bIsRescued; }

	UFUNCTION()
		int32 GetMissionID() { return MissionID; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//���ͷ����� ������ ������ ��Ÿ���� ������ �̺�Ʈ�� ���� üũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* InteractionTrigger;

	//���̵� �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RescueGuideMesh;

	//�̼��� �����ϱ� ���� ������ ���� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* InfoWidget;

	//���ε��� �̼��� ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission")
		int32 MissionID;

private:
	//�ҹ�� ���Ӹ�� ���۷���
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef; 

	//���� �����ǰ� �ִ���?
	UPROPERTY()
		bool bIsBeingRescued = false ;
	
	//�̹� ���� �Ǿ�����?
	UPROPERTY()
		bool bIsRescued =  false;

	//Activate �Ǿ�����? (=��ȣ�ۿ��� ��������?)
	UPROPERTY()
		bool bIsActivated = false;
};
