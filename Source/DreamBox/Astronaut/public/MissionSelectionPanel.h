// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautControllableInterface.h"
#include "GameFramework/Actor.h"
#include "MissionSelectionPanel.generated.h"

UCLASS()
class DREAMBOX_API AMissionSelectionPanel : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissionSelectionPanel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// ���� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* MainWidget;

public:
	// �������̽����� ��ӹ��� �Լ� ����. MissionSelectionPanel������ HiddenInGame ������ ����
	virtual void SetStatus_Implementation(bool Value) override;

	// �������̽����� ��ӹ��� �Լ� ����. ���� ��ȯ
	virtual AActor* GetActor_Implementation() override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void Activate();

	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void Deactivate();

	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LockMission(int32 Mission);

	UFUNCTION(BlueprintPure)
		class AAstronautCharacter* GetLocalPlayer();
};