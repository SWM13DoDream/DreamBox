// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "RescueGoal.generated.h"

/*
 - Name        : ARescueGoal
 - Description : 구조되고 있는 캐릭터를 내려놓을 포인트를 나타내고, 구조 종료 이벤트를 호출하는 액터
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

	//플레이어가 해당 포인트로 왔다면, TriggerRescurEvent 호출  
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
	//최상위 루트 컴포넌트
	UPROPERTY()
		USceneComponent* DefaultSceneRoot;

	//구조 종료 포인트를 나타내는 콜리전 볼륨. 오버랩 시 구조 종료 이벤트 호출
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* EventTrigger;
	
	//구조 종료 포인트를 시각적으로 보여주는 가이드 메시 (밝은 테두리 원)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* DestinationGuideMesh;

	//구조 종료 포인트를 시각적으로 보여주는 가이드 메시 (화살표)
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DestinationArrowMesh;

public:
	//구출해야할 인원 수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission")
		int32 TargetRescueCount = 4; 

	UPROPERTY(EditAnywhere, Category = "Mission")
		TArray<int32> RescueMissionIdList;

private:
	//플레이어 캐릭터 레퍼런스
	UPROPERTY()
		class AFirefighterCharacter* FirefighterCharacterRef;

	//C++ 딜레이 사용 위한 타이머 핸들 : 미사용
	UPROPERTY()
		struct FTimerHandle WaitHandle;

protected:
	//게임모드 레퍼런스
	UPROPERTY(BlueprintReadOnly)
		class AFirefighterGamemode* GamemodeRef;

	//현재까지 구출한 인원 수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CurrentRescueCount = 0;

	//미션 이벤트에 의해 활성화가 되었는지?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsActivated;
};
