// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautControllableInterface.h"
#include "GamemodeArbiter.generated.h"

/*
 - Name        : AGamemodeArbiter
 - Description : Map�� ��ġ�Ǿ� Gamemode�� �߰��ϴ� C++ ����
 - Date        : 2022/09/03 DEVroar
*/

UCLASS()
class DREAMBOX_API AGamemodeArbiter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamemodeArbiter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Gamemode���� �����ϴ� SignDisplay ���� ������Ʈ ���۷��� �迭
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SignDisplayControllables;

	// Gamemode���� �����ϴ� InteractionTrigger ���� ������Ʈ ���۷��� (���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainInteractionControllable;

	// Gamemode���� �����ϴ� InteractionTrigger ���� ������Ʈ ���۷��� �迭 (���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubInteractionControllables;

	// Gamemode���� �����ϴ� ControllableStaticMesh ���� ������Ʈ ���۷��� (���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainStaticMeshControllable;

	// Gamemode���� �����ϴ� ControllableStaticMesh ���� ������Ʈ ���۷��� �迭 (���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubStaticMeshControllables;

	// Gamemode���� �����ϴ� Destination Guide ���� ������Ʈ ���۷��� (���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainGuideControllable;

	// Gamemode���� �����ϴ� Destination Guide ���� ������Ʈ ���۷��� �迭 (���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubGuideControllables;
};
