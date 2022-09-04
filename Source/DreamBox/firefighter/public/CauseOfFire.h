// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "CauseOfFire.generated.h"

/*
 - Name        : ACauseOfFire
 - Description : ȭ�� ���� ���� �̼��� ���� ����. �÷��̾�� "Investigation" Ÿ���� ��ȣ�ۿ��� ��
 - Date        : 2022/09/02 LJH
*/

UCLASS()
class DREAMBOX_API ACauseOfFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACauseOfFire();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(EEndPlayReason::Type Reason) override;

	UFUNCTION()
		void InteractionTriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp
			, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void InteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void TryActivateMissionActor(int32 PlayerId, int32 NewMissionId, int32 Variable);

	UFUNCTION(BlueprintPure)
		bool GetIsActivated() { return bIsActivated; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: 
	UPROPERTY(EditAnywhere)
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
		USphereComponent* InteractionTrigger;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* GuideMesh; 

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* EffectParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UWidgetComponent* InvestigateInfoWidgetComponent;

public: 
	//����ڰ� �ٰ��� �� ��� ���� Ŭ���� ���۷���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		TSubclassOf<UUserWidget> InvestigateInfoWidgetClass;

	//�� ���Ϳ� �Ҵ�� �̼�ID
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 MissionID;

	//Activate �Ǿ� ���� ������ ��ȣ�ۿ� �Ұ�
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsActivated; 

	//���� Ŭ������ ���� �ؽ�Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (MultiLine = true))
		FText InfoText_;

private: 	
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef; 

	UPROPERTY()
		UUserWidget* InvestigateInfoWidgetRef;
};
