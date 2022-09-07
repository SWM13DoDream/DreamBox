// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "MissionTrigger.generated.h"

/*
 - Name        : AMissionTrigger
 - Description : 특정 미션을 추가 & 업데이트 & 제거
                 미션 Flow의 조정을 위해 특정 구간을 Block
 - Date        : 2022/09/05 LJH
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

	//플레이어가 MissionUpdate 볼륨에 오버랩 된다면, ID에 따라 미션을 업데이트
	UFUNCTION()
		void MissionUpdateEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor
							, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//플레이어가 PrevMissionCheckTrigger 볼륨에 오버랩 된다면, 이전 미션을 완료했는지 판단
	UFUNCTION()
		void PrevMissionCheckBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	//미션 델리게이트를 호출 (제거/추가 구분하여)
	UFUNCTION()
		void UpdateMissionDelegate();

	//특정 미션이 추가 되었을 경우, 조건에 따라 이 볼륨의 콜리전 채널을 overlapAll으로 업데이트
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

	//할당된 미션ID의 진행도를 올리는 볼륨인지?
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsMissionGoalVolume = false;

	//루트 컴포넌트
	UPROPERTY(EditAnywhere)
		USceneComponent* DefaultSceneRoot;

	//플레이어의 오버랩으로 이벤트를 트리거
	UPROPERTY(EditAnywhere)
		UBoxComponent* MissionUpdateTrigger; 

	//이전 미션 완료 여부를 판단하는 트리거
	UPROPERTY(EditAnywhere)
		UBoxComponent* PrevMissionCheckTrigger;

private:
	//게임모드 레퍼런스
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef;
};
