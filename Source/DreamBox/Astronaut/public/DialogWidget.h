// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DialogWidget.generated.h"

/*
 - Name        : UDialogWidget
 - Description : 우주 비행사 컨텐츠의 다이얼로그 위젯 베이스 C++ 코드
 - Date        : 2022/09/01 DEVroar
*/

UCLASS()
class DREAMBOX_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// User Widget 파생 클래스 기본 생성자
	UDialogWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// 다이얼로그 내용 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* ContentText;

public:
	// 멤버 변수 세팅 함수
	UFUNCTION(BlueprintCallable)
		void SetIdentity(FText Value);

public:
	// 다이얼로그 내용
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Content;
};
