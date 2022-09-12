// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Engine/DataTable.h"
#include "SScriptStruct.generated.h"

UCLASS()
class DREAMBOX_API ASScriptStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASScriptStruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

USTRUCT(Atomic, BlueprintType)
struct FScriptStructure : public FTableRowBase
{
	GENERATED_BODY()

public:
	FScriptStructure() : Script(""), TimeLength(2.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString Script;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float TimeLength;
};