// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Introduce.generated.h"

/*
- Name			: AIntroduce
- Description	: 각 종 Floating Widget을 담당하는 Actor
- Date			: 2022-07-11
*/

UCLASS()
class DREAMBOX_API AIntroduce : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntroduce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
		UWidgetComponent* Widget;
};
