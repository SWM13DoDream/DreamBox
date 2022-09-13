// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "GameFramework/GameModeBase.h"
#include "AstronautGamemode.generated.h"

/*
 - Name        : AAstronautGamemode
 - Description : 우주비행사 메인 게임모드
 - Date        : 2022/07/26 DEVroar
*/

// 우주비행사의 임무 목록을 ENUM으로 관리
UENUM(BlueprintType)
namespace EAstronautMissionType
{
	enum Type
	{
		/** 탐사선 임무 - 월면 기지에서 수행 */
		LEM,

		/** 사령선 임무 - 루나 게이트웨이에서 수행 */
		CSM
	};
}

UCLASS()
class DREAMBOX_API AAstronautGamemode : public AGameModeBase
{
	GENERATED_BODY()

private:
	// 사령선 도착 주기 상수값
	const int32 TIME_PERIOD = 300;

	// 서브 임무 개수 상수값
	const int32 SUBMISSION_NUM = 6;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 1초마다 실행되는 타이머 핸들러
	void HandleTimer();
	FTimerHandle TimerHandler;

	// 미션 위젯 표시 TEXT 상수값. 파생 BP에서 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText MAIN_MISSION_INIT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText MAIN_MISSION_DONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		TArray<FText> SUB_MISSION_TEXT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText SUB_MISSION_DONE;

public:
	// 캐릭터 타이머 위젯 컨트롤러
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		UTimerWidget* CharacterTimerController;

	// 캐릭터 미션 위젯 컨트롤러
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		UMissionWidget* CharacterMissionController;

	// 게임모드 뷰포트 중계 액터 컨트롤러
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		AGamemodeArbiter* Arbiter;

public:
	// 랜덤 미션을 생성하고 레벨에 있는 액터를 조작하여 게임을 세팅하는 함수
	// 무결성을 위해 BeginPlay 호출 시가 아니라 Arbiter 등록 시에 호출됨
	UFUNCTION(BlueprintCallable)
		void InitializeMissions();

	// 서브 미션을 활성화 및 구성하는 함수
	UFUNCTION(BlueprintCallable)
		void ConsistSubMission(int32 Index);

	// 서브 미션을 비활성화하는 함수
	UFUNCTION(BlueprintCallable)
		void UnsetSubMission(int32 Index);

	// 메인 미션 (통신 장치 부착)을 수행한 후 InteractionTrigger로부터 호출되는 함수
	UFUNCTION(BlueprintCallable)
		void DoMainMission();

	// 서브 미션을 수행한 후 InteractionTrigger로부터 호출되는 함수
	UFUNCTION(BlueprintCallable)
		void DoSubMission(int32 Index);

	// 임무를 마치고 출발할 수 있는 시간대인지 확인 (타이머 00:00 ~ 00:20, 4:40 ~ 5:00)
	UFUNCTION(BlueprintCallable)
		bool IsAboardable();

	// Arbiter beginplay 시 호출되는 컨트롤러 등록 함수
	UFUNCTION(BlueprintCallable)
		void RegisterArbiter(class AGamemodeArbiter* Controller);

	// 캐릭터 beginplay 시 호출되는 타이머/미션 위젯 컨트롤러 등록 함수
	UFUNCTION(BlueprintCallable)
		void RegisterWidgetControllers(class UTimerWidget* Timer, class UMissionWidget* Mission);

	// 캐릭터 임무 선택 시 호출되는 플레이어 임무 시작 함수 (위치 변경, 임무 세팅 등)
	UFUNCTION(BlueprintCallable)
		void InitializeMission(class AAstronautCharacter* Target, int32 Mission);

	// 특수 기능 함수: 시퀀서를 호출하여 화면 크로스페이드
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void PlayCrossFade();

	// 특수 기능 함수: 탐사선 외내부 이동에 따른 캐릭터 위치 변경
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void MoveLEM(bool bIsEntering);

public:
	// bool 타입으로 메인 미션 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bIsMissionDone;

	// TArray<bool> 타입으로 서브 미션 관리 (Expected Length = 6)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<bool> bIsSubmissionDone;

	// TArray<int> 타입으로 랜덤으로 선택된 서브 미션 관리 (Expected Length = 3)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<int> RandomSubmissionIndices;

	// Text 타입의 메인 미션 위젯 표시값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FText MainMissionText;

	// TArray<FText> 타입의 서브 미션 위젯 표시값 (Max Length = 3)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<FText> SubMissionText;

	// 플레이어가 움직일 수 있는지 여부를 관리. bMovable = false인 경우 타이머 또한 정지함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool bMovable;

	// 타이머에 표시되는 시간을 관리. TIME_PERIOD가 사령선이 도착하는 한 주기를 나타냄 (현재 설정: 5분)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int32 Time;

private:
	// 무결성이 보장된 첫 타이머 동작 (1s) 시점 로직 호출을 위한 임시 변수
	bool bInitializeFlag;
};
