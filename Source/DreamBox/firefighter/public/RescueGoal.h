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
 - Description : 구조되고 있는 캐릭터를 내려놓을 포인트를 나타내고, 구조 종료 이벤트를 호출하는 액터
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

	//플레이어가 해당 포인트로 왔다면, TriggerRescurEvent 호출  
	UFUNCTION()
		void TriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//구조 종료 포인트를 나타내는 콜리전 볼륨. 오버랩 시 구조 종료 이벤트 호출
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* EventTrigger;

	//바인딩할 미션의 ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission")
		int32 MissionID;

	//구출해야할 인원 수
	UPROPERTY(EditAnywhere, Category = "Mission")
		int32 TargetRescueCount; 

private:
	//현재까지 구출한 인원 수
	UPROPERTY()
		int32 CurrentRescueCount;

	//게임모드 레퍼런스
	UPROPERTY()
		AFirefighterGamemode* GamemodeRef;

	//플레이어 캐릭터 레퍼런스
	UPROPERTY()
		AFirefighterCharacter* FirefighterCharacterRef;

	//C++ 딜레이 사용 위한 타이머 핸들 : 미사용
	UPROPERTY()
		FTimerHandle WaitHandle;
};
