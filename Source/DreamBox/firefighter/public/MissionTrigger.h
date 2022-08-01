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
	//이 트리거 볼륨에 할당된 미션 ID 
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 MissionID = 0;

	//초기 콜리전 옵션 설정 (Initial 미션일 경우 초반부터 Overlap)
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsRequirePrevMission = false;

	//이 트리거 볼륨을 활성화(BlockAll -> OverlapAll) 하기 위해 미리 완료 시켜야 할 미션들
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 PrevMissionID = -1;

	//자동으로 미션을 활성화 할 것인지 여부
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsAutoActivate = false;

	//할당된 미션ID를 기반으로 제거 델리게이트를 호출할 것인지?
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsRemoveVolume = false;

	//루트 컴포넌트
	UPROPERTY(EditAnywhere)
		USceneComponent* DefaultSceneRoot;

	//플레이어의 오버랩으로 이벤트를 트리거
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* TriggerVolume;

private:
	UPROPERTY()
		AFirefighterGamemode* GamemodeRef;
};
