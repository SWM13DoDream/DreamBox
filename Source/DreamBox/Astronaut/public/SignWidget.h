// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AstronautStructBase.h"
#include "SignWidget.generated.h"

/*
 - Name        : USignWidget
 - Description : 우주 비행사 컨텐츠의 표지판 위젯 베이스 C++ 코드
 - Date        : 2022/09/02 DEVroar
*/

UCLASS()
class DREAMBOX_API USignWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// User Widget 파생 클래스 기본 생성자
	USignWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// 표지판 컨텐츠 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* SubtitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* DescriptionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* StateText;

public:
	// 멤버 변수 세팅 함수
	UFUNCTION(BlueprintCallable)
		void SetIdentity(FSignStruct Value);

	// 시설 상태에 따라 StateText를 편집하는 함수. SlateColor 기능을 위해 파생 BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void SetStateDisplay(bool bIsStable);

public:
	// 표지판 컨텐츠 내용 (SignStruct 구조체 변수)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSignStruct Content;
};
