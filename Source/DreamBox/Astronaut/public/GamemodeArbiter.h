// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautControllableInterface.h"
#include "GamemodeArbiter.generated.h"

/*
 - Name        : AGamemodeArbiter
 - Description : Map�� ��ġ�Ǿ� ���� ���� - �ƿ����̳� ���͵��� �߰��ϴ� C++ ����
 - Caution     : AstronautGamemode�� �ƴ϶� AstronautCharacter���� ������. (��Ƽ�÷���)
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
	// ���� ����Ʈ ���� MissionSelectionPanel ���� ������Ʈ ���۷���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MissionSelectionControllable;

	// ���� ����Ʈ ���� SignDisplay ���� ������Ʈ ���۷��� �迭
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SignDisplayControllables;

	// ���� ����Ʈ ���� InteractionTrigger ���� ������Ʈ ���۷��� (���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainInteractionControllable;

	// ���� ����Ʈ ���� InteractionTrigger ���� ������Ʈ ���۷��� �迭 (���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubInteractionControllables;

	// ���� ����Ʈ ���� ControllableStaticMesh ���� ������Ʈ ���۷��� (���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainStaticMeshControllable;

	// ���� ����Ʈ ���� ControllableStaticMesh ���� ������Ʈ ���۷��� �迭 (���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubStaticMeshControllables;

	// ���� ����Ʈ ���� Destination Guide ���� ������Ʈ ���۷��� (LEM ���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainGuideControllable;

	// ���� ����Ʈ ���� Destination Guide ���� ������Ʈ ���۷��� �迭 (LEM ���� �̼�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubGuideControllables;

	// ���� ����Ʈ ���� Destination Guide ���� ������Ʈ ���۷��� �迭 (CSM ���� �۾� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> BeforeEVAGuideControllables;

	// ���� ����Ʈ ���� Destination Guide ���� ������Ʈ ���۷��� �迭 (CSM ���� �۾� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> AfterEVAGuideControllables;

	// ���� ����Ʈ ���� EVA Destination Guide ���� ������Ʈ ���۷��� (�̼� ���� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> InEVADefaultControllables;

	// ���� ����Ʈ ���� EVA Destination Guide ���� ������Ʈ ���۷��� (�̼� ���� ��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> InEVAEditControllables;

	// ���� ����Ʈ ���� �޼� GrabUserDisplay ���� ������Ʈ ���۷���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> LeftGrabDisplayControllable;

	// ���� ����Ʈ ���� ������ GrabUserDisplay ���� ������Ʈ ���۷���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> RightGrabDisplayControllable;

public:
	// �̼� ���� ǥ�� TEXT �����. ���� ����Ʈ���� �⺻�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText MAIN_MISSION_INIT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText MAIN_MISSION_DONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		TArray<FText> SUB_MISSION_TEXT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText SUB_MISSION_DONE;
};
