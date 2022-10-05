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
	// 빈 컴포넌트 (루트 컴포넌트를 위해 생성)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* EmptyComponent;

	// 메인 위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* MainWidget;

	// 플레이어 대기 위젯 컴포넌트 (멀티플레이)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* WaitingWidget;

public:
	// 인터페이스에서 상속받은 함수 구현. MissionSelectionPanel에서는 HiddenInGame 설정에 사용됨
	virtual void SetStatus_Implementation(bool Value) override;

	// 인터페이스에서 상속받은 함수 구현. 액터 반환
	virtual AActor* GetActor_Implementation() override;

public:
	// 메인 미션 선택 위젯 활성화
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void Activate();

	// 메인 미션 선택 위젯 비활성화
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void Deactivate();

	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LockMission(int32 Mission);

	// 플레이어 대기 위젯 활성화
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void WaitingForPlayer(const FString& Address);

	// 플레이어 대기 위젯 비활성화
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void StopWaitingPlayer();

	UFUNCTION(BlueprintCallable)
		void SelectMission(int32 Mission);

	UFUNCTION(BlueprintPure)
		class AAstronautCharacter* GetLocalPlayer();
};
