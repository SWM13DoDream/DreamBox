// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "WidgetButton.generated.h"

UCLASS()
class DREAMBOX_API AWidgetButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWidgetButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Body")
		UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, Category = "Button")
		UWidgetComponent* ButtonWidget;
};
