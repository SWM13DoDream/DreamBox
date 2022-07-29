// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "FirefighterGamemode.h"
#include "InjuredCharacter.generated.h"

/*
 - Name        : AInjuredCharacter
 - Description : ĳ���Ͱ� ������ �䱸���� ĳ����
 - Date        : 2022/07/20 LJH
*/

UCLASS()
class DREAMBOX_API AInjuredCharacter : public APawn
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

	/* --- Get/Set �Լ� ----- */
	UFUNCTION(BlueprintCallable)
		bool GetIsBeingRescued() { return bIsBeingRescued; }
	
	UFUNCTION(BlueprintCallable)
		void SetIsRescued(bool NewState) { bIsRescued = NewState; }

	UFUNCTION(BlueprintCallable)
		bool GetIsRescued() { return bIsRescued; }

	UFUNCTION()
		int32 GetMissionID() { return MissionID;  }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
		UCapsuleComponent* CapsuleComponent;

	//ĳ������ ��ü�� ������ ���̷�Ż �޽� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent * Mesh;

	//���ͷ����� ������ ������ ��Ÿ���� ������ �̺�Ʈ�� ���� üũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* InteractionTrigger;

	//���ͷ��� ����Ʈ ����
	UPROPERTY(EditAnywhere)
		UTextRenderComponent* InteractionTextRender;
	
	//���̵� �޽� ������Ʈ
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RescueGuideMesh;

	//���ε��� �̼��� ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission")
		int32 MissionID;

private:
	//�ҹ�� ���Ӹ�� ���۷���
	UPROPERTY()
		AFirefighterGamemode* GamemodeRef; 

	//���� �����ǰ� �ִ���?
	UPROPERTY()
		bool bIsBeingRescued;

	UPROPERTY()
		bool bIsRescued;
};
