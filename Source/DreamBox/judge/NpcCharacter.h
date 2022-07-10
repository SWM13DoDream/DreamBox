// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "NpcCharacter.generated.h"

UCLASS()
class DREAMBOX_API ANpcCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpcCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Widget")
		UWidgetComponent* ScriptWidget;

	UPROPERTY(VisibleAnywhere, Category = "Chair")
		UStaticMeshComponent* StaticMesh;
};
