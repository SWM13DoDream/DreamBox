// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AstronautStructBase.h"
#include "InteractionWidget.generated.h"

/*
 - Name        : UInteractionWidget
 - Description : 우주 비행사 컨텐츠의 인터렉션 위젯 베이스 C++ 코드
 - Date        : 2022/09/02 DEVroar
*/

UCLASS()
class DREAMBOX_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// User Widget 파생 클래스 기본 생성자
	UInteractionWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// 미션 내용 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* IntroductionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* InteractionText;

	// 해당 위젯을 컴포넌트로 가지는 InteractionTrigger 제어 변수.
	// 이 변수의 값은 InteractionTrigger의 BeginPlay에서 초기화됨
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AInteractionTrigger* Controller;

public:
	// 멤버 변수 및 제어 변수 세팅 함수
	UFUNCTION(BlueprintCallable)
		void SetIdentity(class AInteractionTrigger* Parent, FInteractionStruct Value);

	// 인터렉션 버튼이 눌렸을 때 호출되는 함수. InteractionTrigger의 멤버 메서드 호출
	UFUNCTION(BlueprintCallable)
		void OnInteract();

	// 위젯 애니메이션 재생. 파생 BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void Animate(bool bIsAppearing);

private:
	// 인터렉션 위젯 내용
	FInteractionStruct Content;
};
