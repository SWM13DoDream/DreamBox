// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MissionWidget.generated.h"

/*
 - Name        : UMissionWidget
 - Description : 우주 비행사 컨텐츠의 미션 위젯 베이스 C++ 코드
 - Date        : 2022/09/02 DEVroar
*/

UCLASS()
class DREAMBOX_API UMissionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// User Widget 파생 클래스 기본 생성자
	UMissionWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// 미션 내용 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* MainContentText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* SubContentText;

	// AstronautCharacter 타입으로 미리 캐스팅되는 로컬 플레이어 레퍼런스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AAstronautCharacter* LocalPlayer;

public:
	// Gamemode에서 메인 미션 상태 변경 시 디스플레이 업데이트. Unicode를 사용하므로 파생 BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void UpdateMainMissionDisplay();

	// Gamemode에서 서브 미션 상태 변경 시 디스플레이 업데이트. Unicode를 사용하므로 파생 BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void UpdateSubMissionDisplay();
};
