// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautStructBase.h"
#include "AstronautControllableInterface.h"
#include "SignDisplay.generated.h"

/*
 - Name        : ASignDisplay
 - Description : 우주 비행사 컨텐츠의 표지판 위젯을 관리하는 C++ 액터
 - Date        : 2022/09/01 DEVroar
*/

UCLASS()
class DREAMBOX_API ASignDisplay : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASignDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// 표지판 위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* WidgetComponent;

	// SignWidget 타입으로 미리 캐스팅되는 UserWidget 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class USignWidget* Widget;

public:
	// C++의 BeginPlay가 호출된 직후 타이밍에 BP에서 구현된 시작 시 함수를 호출하도록 하는 implementable 함수
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void Initialize();

	// 표지판 내용 세팅 함수
	UFUNCTION(BlueprintCallable)
		void SetSignContent(FSignStruct Value);

	// 시설 상태 제어 함수
	UFUNCTION(BlueprintCallable)
		void SetStability(bool Value);

public:
	// 인터페이스에서 상속받은 함수 구현. SignDisplay에서는 Stability 설정에 사용됨
	virtual void SetStatus_Implementation(bool Value) override;

private:
	// 시설 상태 제어 변수
	bool bIsStable;
};
