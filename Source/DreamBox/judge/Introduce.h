// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Introduce.generated.h"

/*
- Name			: AIntroduce [ �̸����� ��� ]
- Description	: �� �� Floating Widget�� ����ϴ� Actor
- Date			: 2022-08-12
- Version		: 1.0.1 ver
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

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ROOT")
		USceneComponent* SceneComponent;

	// Float Widget�� �ǹ��ϴ� WidgetComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
		UWidgetComponent* Widget;

	// Float Widget�� �ǹ��ϴ� WidgetComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		UWidgetComponent* NextPage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Petition")
		bool isNextPage;
};
