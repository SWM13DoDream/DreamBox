// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "MissionManager.generated.h"

UCLASS()
class DREAMBOX_API AMissionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissionManager();

	UFUNCTION()
		void UpdateMissionWidgetEvent(int32 MissionID, int32 Variable);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateMission(int32 MissionID, int32 Variable);

	UFUNCTION(BlueprintImplementableEvent)
		void AddNewMission(int32 NewMissionID);

	UFUNCTION()
		void RemoveMission(int32 TargetMissionID);

	UFUNCTION(BlueprintPure)
		UUserWidget* GetMissionWidgetRef() const { return MissionListWidgetRef; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY()
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionListWidget;

private:
	UPROPERTY()
		UUserWidget* MissionListWidgetRef;
};
