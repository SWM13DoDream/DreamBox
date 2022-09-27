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
	// 메인 위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* MainWidget;

public:
	// 인터페이스에서 상속받은 함수 구현. MissionSelectionPanel에서는 HiddenInGame 설정에 사용됨
	virtual void SetStatus_Implementation(bool Value) override;

	// 인터페이스에서 상속받은 함수 구현. 액터 반환
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
