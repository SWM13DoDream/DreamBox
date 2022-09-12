// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "DialogController.generated.h"

/*
 - Name        : ADialogController
 - Description : 우주 비행사 컨텐츠의 다이얼로그 위젯을 관리하는 C++ 액터
 - Date        : 2022/09/01 DEVroar
*/

UCLASS()
class DREAMBOX_API ADialogController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 다이얼로그 위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* WidgetComponent;

	// DialogWidget 타입으로 미리 캐스팅되는 UserWidget 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class UDialogWidget* Widget;

	// AstronautGamemode 타입으로 미리 캐스팅되는 Gamemode 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AAstronautGamemode* Gamemode;

public:
	// 우주과학자 인트로 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogIntro();
	
	// 우주과학자 타이머 중간 지점 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogMid();

	// 우주과학자 임무 완료 임박 지점 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogApprox();

	// 다이얼로그 세팅 함수 - BP로 작업하면 더러워서 클린코딩을 위해 구현됨
	UFUNCTION(BlueprintCallable)
		void SetDialogContent(FText Value);

private:	
	// 타이머로 등록되어 매 초마다 Gamemode의 시간을 체크, 특정 시점에 타 함수 호출
	FTimerHandle UpdateStateHandler;
	void UpdateState();

	// FSM Concept로 관리되는 다이얼로그 상태 관리 변수
	int32 DialogState;
};
