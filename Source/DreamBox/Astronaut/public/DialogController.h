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

	// AstronautCharacter 타입으로 미리 캐스팅되는 로컬 플레이어 레퍼런스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AAstronautCharacter* LocalPlayer;

	// 대사가 재생되고 있는 동안은 다른 대사가 끼어들 수 없음
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDialogLock;

	// 선택된 우주비행사 임무
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Mission;

	// 멀티플레이어 시, 다른 플레이어로부터 종료 메시지가 온 경우 겹치지 않도록 register
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bDoneMessageRegistered;

	// 우주비행사 멀티플레이 여부
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bInMultiplay;

	// 우주비행사 멀티플레이 관련 다이얼로그 표시 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bMultiplayDialogFlag;

public:
	// 다이얼로그 컨트롤러 액터의 활성화 상태 설정
	UFUNCTION(BlueprintCallable)
		void SetActivated(bool bValue, int32 SelectedMission, bool bMultiplay);

	// 우주비행사 LEM 인트로 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogIntro();
	
	// 우주비행사 LEM 타이머 중간 지점 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogMid();

	// 우주비행사 LEM 임무 완료 임박 지점 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogApprox();

	// 우주비행사 CSM 인트로 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void CSMDialogIntro();

	// 우주비행사 CSM 중간 지점 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void CSMDialogMid();

	// 우주비행사 멀티플레이 LEM 시작 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void LEMMultiplayIntro();

	// 우주비행사 멀티플레이 LEM 통신 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void LEMDoneMessageFromCSM();

	// 우주비행사 멀티플레이 CSM 통신 다이얼로그 이벤트. BP에서 구현
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void CSMDoneMessageFromLEM();

	// 다이얼로그 세팅 함수 - BP로 작업하면 더러워서 클린코딩을 위해 구현됨
	UFUNCTION(BlueprintCallable)
		void SetDialogContent(FText Value);

	// 멀티플레이에서 다른 플레이어의 임무가 끝났을 때 DoneMessageDialog 출력
	UFUNCTION(BlueprintCallable)
		void AnnounceMissionDoneFromOther();

private:	
	// 타이머로 등록되어 매 초마다 Gamemode의 시간을 체크, 특정 시점에 타 함수 호출
	FTimerHandle UpdateStateHandler;
	void UpdateState();

	// FSM Concept로 관리되는 다이얼로그 상태 관리 변수
	int32 DialogState;
};
