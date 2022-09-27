// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "InfoWidget.generated.h"

/*
 - Name        : UInfoWidget
 - Description : 우주 비행사 컨텐츠의 정보 위젯 베이스 C++ 코드
			   : ImplementableEvent 기능만 정의되어있어 파생 BP에서 구현
 - Date        : 2022/09/26 DEVroar
*/

UCLASS()
class DREAMBOX_API UInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// User Widget 파생 클래스 기본 생성자
	UInfoWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// 로컬 플레이어
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
		class AAstronautCharacter* LocalPlayer;

	// 활성화 상태 변수 (주로 버튼 인터렉션에서 상태 체크)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bActivated;

	// 위젯 활성화
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "NeedImplementation")
		void Activate();

	// 위젯 비활성화
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "NeedImplementation")
		void Deactivate();
};
