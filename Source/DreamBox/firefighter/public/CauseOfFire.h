// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "CauseOfFire.generated.h"

/*
 - Name        : ACauseOfFire
 - Description : 화재 원인 조사 미션을 위한 액터. 플레이어는 "Investigation" 타입의 상호작용을 함
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
	//사용자가 다가갈 시 띄울 위젯 클래스 레퍼런스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		TSubclassOf<UUserWidget> InvestigateInfoWidgetClass;

	//본 액터에 할당된 미션ID
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 MissionID;

	//Activate 되어 있지 않으면 상호작용 불가
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsActivated; 

	//위젯 클래스의 본문 텍스트
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (MultiLine = true))
		FText InfoText_;

private: 	
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef; 

	UPROPERTY()
		UUserWidget* InvestigateInfoWidgetRef;
};
