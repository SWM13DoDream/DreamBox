// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "StairPortal.generated.h"

/*
 - Name        : AStairPortal 
 - Description : 계단 컨트롤 개선을 위한 자동 이동 포털
                 기본 로직은 1층->3층->2층->... 이지만,
				 특정 미션이 추가될 때 1층->2층, 2층->3층 등의 
				 워프가 가능하도록 커스텀할 수 있다
 - Date        : 2022/09/04 LJH
*/

UCLASS()
class DREAMBOX_API AStairPortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStairPortal();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void ActivatePortal(int32 PlayerID, int32 MissionID, int32 Variable);

	//플레이어가 오버랩 된다면, ID에 따라 미션을 업데이트
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	//루트 컴포넌트
	UPROPERTY()
		USceneComponent* DefaultSceneRoot;

	// 플레이어의 오버랩으로 이벤트를 트리거
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* TriggerVolume;

	//워프할 위치를 담음
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		TArray<AStairPortal*> TeleportPointArray;

	//기본 워프 타겟 위치
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 DefaultDestination; 

	//특정 미션이 진행될 때만 워프할 타겟 위치
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 MissionDestination = -1;

	//첫 번째 층 포탈인지?
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		bool bIsFirstFloor = false;

	//워프 위치가 "MissionDestination"으로 바뀔 미션ID 
	UPROPERTY(EditAnywhere, Category = "Gameplay")
		int32 TargetMissionID;

private:
	//게임모드 레퍼런스
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef;

	UPROPERTY()
		ACharacter* PlayerCharacterRef;

	//C++ 딜레이 사용 위한 타이머 핸들 
	UPROPERTY()
		struct FTimerHandle WaitHandle;
};
