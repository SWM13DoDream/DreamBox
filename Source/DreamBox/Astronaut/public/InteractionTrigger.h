// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautStructBase.h"
#include "AstronautControllableInterface.h"
#include "InteractionTrigger.generated.h"

/*
 - Name        : AInteractionTrigger
 - Description : 우주 비행사 컨텐츠의 인터렉션 위젯을 관리하는 C++ 액터
 - Date        : 2022/09/02 DEVroar
*/

UCLASS()
class DREAMBOX_API AInteractionTrigger : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 인터렉션 위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* WidgetComponent;

	// 인터렉션 박스 콜리전 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UBoxComponent* BoxCollision;

	// InteractionWidget 타입으로 미리 캐스팅되는 UserWidget 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class UInteractionWidget* Widget;

	// AstronautGamemode 타입으로 미리 캐스팅되는 Gamemode 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AAstronautGamemode* Gamemode;

public:
	// 이 C++에서 BeginPlay 호출 후 BP에서 파생된 InitializeMode() 이벤트 실행
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void InitializeMode();

	// 위젯 내용 세팅 함수
	UFUNCTION(BlueprintCallable)
		void SetInteractionContent(FInteractionStruct Content);

	// BoxTrigger에 액터 진입 시 호출되는 함수, 여기 C++에서 Validity 처리도 한번에 수행함
	UFUNCTION(BlueprintCallable)
		void OnTriggerEnter(class AActor* OtherActor);

	// BoxTrigger에서 액터 퇴장 시 호출되는 함수, 여기 C++에서 Validity 처리도 한번에 수행함
	UFUNCTION(BlueprintCallable)
		void OnTriggerExit(class AActor* OtherActor);

	// 자식 위젯의 버튼이 눌렸을 때 호출되는 함수
	UFUNCTION(BlueprintCallable)
		void OnInteract();

	// bIsInteractable을 false로 설정하고 미션 가이드 액터를 비활성화하는 함수
	UFUNCTION(BlueprintCallable)
		void Unset();

public:
	// 인터렉션 모드 (D_Interaction의 key값)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName InteractionMode;

	// 상호작용 가능한 상태인지 확인
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsInteractable;

	// 자식 위젯이 활성화된 상태인지 확인
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsAvailable;

	// 인터렉션 내용이 바뀔 수 있는 InteractionTrigger 인스턴스인지 확인
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasVariableMode;

public:
	// 인터페이스에서 상속받은 함수 구현. InteractionTrigger에서는 Unset 설정에 사용됨
	virtual void SetStatus_Implementation(bool Value) override;

private:
	// UE4 C++에서 Delay 사용을 위한 타이머 핸들러
	FTimerHandle DelayHandler;

	// Trigger 대상 플레이어 액터의 Validity 체크
	bool IsValidPlayer(class AActor* TargetActor);
};
