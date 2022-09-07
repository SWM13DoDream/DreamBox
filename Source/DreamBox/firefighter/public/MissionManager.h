// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "MissionManager.generated.h"

/*
 - Name        : AMissionManager
 - Description : 미션 위젯을 소유하고 있는 액터. 플레이어와 위젯간의 통신 경로
 - Date        : 2022/09/04 LJH
*/

UCLASS()
class DREAMBOX_API AMissionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissionManager();

	//미션ID와 Variable을 기반으로 미션을 추가 및 업데이트를 함
	UFUNCTION()
		void UpdateMissionWidgetEvent(int32 MissionID, int32 Variable);

	//블루프린트 이벤트) 미션을 Variable 만큼 업데이트 한다
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateMission(int32 MissionID, int32 Variable);

	//블루프린트 이벤트) 미션을 새로 추가한다
	UFUNCTION(BlueprintImplementableEvent)
		void AddNewMission(int32 NewMissionID);

	//블루프린트 이벤트) 미션을 강제 완료 시킨다
	UFUNCTION()
		void RemoveMission(int32 TargetMissionID);

	//미션 위젯 레퍼런스를 반환
	UFUNCTION(BlueprintPure)
		UUserWidget* GetMissionWidgetRef() const { return MissionListWidgetRef; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//루트 컴포넌트
	UPROPERTY()
		USceneComponent* DefaultSceneRoot;
	
	//미션 위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionListWidget;

private:
	//미션 위젯 레퍼런스 (MissionListWidget->GetWidget())
	UPROPERTY()
		UUserWidget* MissionListWidgetRef;
};
