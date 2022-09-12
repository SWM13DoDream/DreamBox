// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "AstronautStructBase.h"
#include "ExplanationWidget.generated.h"

/*
 - Name        : UExplanationWidget
 - Description : 우주 비행사 컨텐츠의 설명 위젯 베이스 C++ 코드
 - Date        : 2022/09/01 DEVroar
*/

UCLASS()
class DREAMBOX_API UExplanationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// User Widget 파생 클래스 기본 생성자
	UExplanationWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// 설명 컨텐츠 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* SubtitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* NavUpperTitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* NavUpperContentText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* NavLowerTitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* NavLowerContentText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* DescriptionText;

public:
	// 멤버 변수 세팅 함수
	UFUNCTION(BlueprintCallable)
		void SetIdentity(FExplanationStruct Value);

	// 이미지 세팅 함수, BP Slate Brush 기능 사용을 위해 파생 BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void SetImage(UTexture* Texture);

public:
	// 설명 컨텐츠 내용 (ExplanationStruct 구조체 변수)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FExplanationStruct Content;
};
