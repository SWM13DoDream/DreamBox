// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AstronautGamemode.h"
#include "TimerWidget.generated.h"

/*
 - Name        : UTimerWidget
 - Description : 우주 비행사 컨텐츠의 타이머 위젯 베이스 C++ 코드
 - Date        : 2022/09/02 DEVroar
*/

UCLASS()
class DREAMBOX_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// User Widget 파생 클래스 기본 생성자
	UTimerWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

protected:
	// TitleText에 표시되는 TEXT 상수값. 파생 BP에서 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText TITLE_DONEABLE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText TITLE_NOT_DONEABLE;
	
public:
	// 타이머 내용 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* ContentText;

	// AstronautGamemode 타입으로 미리 캐스팅되는 Gamemode 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AAstronautGamemode* Gamemode;

public:
	// Gamemode에서 매 초마다 호출되어 타이머 디스플레이 체크
	UFUNCTION(BlueprintCallable)
		void UpdateDisplay();

	// UpdateDisplay 호출 시마다 OuterWidget의 렌더 로테이션 변경, 파생 BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void ChangeTimerRotation(float Angle);

	// Gamemode->bIsAboardable 내용이 바뀔 때 SlateColor를 이용한 컨텐츠 텍스트 색상 변경, 파생 BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void ChangeTimeColor(bool bIsAboardable);

private:
	// ChangeTimeColor를 상태 변경 (Rising/Falling) 시에만 호출하도록 하는 aboardable 이전 상태 저장 변수
	bool bWasAboardable;
};
