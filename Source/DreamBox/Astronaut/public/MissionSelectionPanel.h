// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "GameFramework/Actor.h"
#include "MissionSelectionPanel.generated.h"

UCLASS()
class DREAMBOX_API AMissionSelectionPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissionSelectionPanel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
