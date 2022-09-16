// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/AstronautGamemode.h"
#include "../public/MissionWidget.h"
#include "../public/TimerWidget.h"
#include "../public/GamemodeArbiter.h"
#include "../public/AstronautCharacter.h"

void AAstronautGamemode::BeginPlay() 
{
	Super::BeginPlay();

	// 메인 미션 관련 변수 초기화 (서브 미션은 InitializeMissions에서 처리)
	bIsMissionDone = false;
	MainMissionText = MAIN_MISSION_INIT;

	// 1초에 한 번씩 호출되는 타이머를 세팅. 초기값으로 설정
	Time = TIME_PERIOD;
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AAstronautGamemode::HandleTimer, 1.0f, true, 1.0f);

	bInitializeFlag = false;
}

void AAstronautGamemode::InitializeMissions()
{
	// 6개 옵션 중 3개를 선택하는 이진 선택자 목록 (ex. 7 = 000111, 11 = 001011, 13 = 001101 ... ) 
	int32 RandomMissionIndices[] = { 7, 11, 13, 14, 19, 21, 22, 25, 26, 28, 35, 37, 38, 41, 42, 44, 49, 50, 52, 56 };
	int32 RandomMissionSelector = RandomMissionIndices[FMath::RandRange(0, 19)];

	// 랜덤 선택자에 따라서 bool[SUBMISSION_NUM] 타입인 bIsSubmissionDone를 초기화 및 할당
	for (int i = 0; i < SUBMISSION_NUM; i++)
	{
		if (RandomMissionSelector % 2 == 1)
		{
			bIsSubmissionDone[i] = true;

			// UnsetSubMission(i)를 쓰지 않고 true 인자를 쓰는 로직을 사용
			// true 인자를 interactiontrigger로 넘기면 게임 시작 시에 발생하는 무결성 문제를 해결 가능
			Arbiter->SubInteractionControllables[i]->SetStatus_Implementation(true);
		}
		else
		{
			RandomSubmissionIndices.Add(i);
			SubMissionText.Add(SUB_MISSION_TEXT[i]);

			ConsistSubMission(i);
		}
		RandomMissionSelector /= 2;
	}
}

void AAstronautGamemode::ConsistSubMission(int32 Index)
{
	Arbiter->SubStaticMeshControllables[Index]->SetStatus_Implementation(true);
}

void AAstronautGamemode::UnsetSubMission(int32 Index)
{
	Arbiter->SubInteractionControllables[Index]->SetStatus_Implementation(false);
}

void AAstronautGamemode::DoMainMission()
{
	bIsMissionDone = true;
	MainMissionText = MAIN_MISSION_DONE;

	Arbiter->MainStaticMeshControllable->SetStatus_Implementation(true);
	Arbiter->MainInteractionControllable->SetStatus_Implementation(false);
	Arbiter->MainGuideControllable->SetStatus_Implementation(false);

	// 미션 위젯 디스플레이 업데이트
	CharacterMissionController->UpdateMainMissionDisplay();
}

void AAstronautGamemode::DoSubMission(int32 Index)
{
	bIsSubmissionDone[Index] = true;
	for (int32 i = 0; i < 3; i++) 
	{ 
		if (RandomSubmissionIndices[i] == Index)
		{
			bIsSubmissionDone[Index] = true;
			SubMissionText[i] = SUB_MISSION_DONE;
		}
	}

	UnsetSubMission(Index);

	// 미션 위젯 디스플레이 업데이트
	CharacterMissionController->UpdateSubMissionDisplay();

	// 가이드 액터 Visibility 설정
	Arbiter->SubGuideControllables[Index]->SetStatus_Implementation(false);
}

bool AAstronautGamemode::IsAboardable()
{
	return Time <= 20 || Time >= (TIME_PERIOD - 20);
}

void AAstronautGamemode::RegisterArbiter(class AGamemodeArbiter* Controller)
{
	Arbiter = Controller;
	InitializeMissions();
}

void AAstronautGamemode::RegisterWidgetControllers(class UTimerWidget* Timer, class UMissionWidget* Mission)
{
	CharacterTimerController = Timer;
	CharacterMissionController = Mission;
}

void AAstronautGamemode::InitializeMission(class AAstronautCharacter* Target, int32 Mission)
{
	if (Mission == EAstronautMissionType::LEM)
	{
		// TODO
	}
	else if (Mission == EAstronautMissionType::CSM)
	{
		// TODO
	}
}

void AAstronautGamemode::HandleTimer()
{
	Time -= 1;
	if (Time < 0) Time = TIME_PERIOD;

	if (CharacterTimerController != nullptr) CharacterTimerController->UpdateDisplay();

	// 첫 타이머 tick에만 호출 (무결성이 보장된 Initialize Logic)
	if (!bInitializeFlag)
	{
		CharacterMissionController->UpdateMainMissionDisplay();
		CharacterMissionController->UpdateSubMissionDisplay();

		// SignDisplay 설정의 경우 widget 초기 구성과 타이밍이 맞지 않을 수 있어 무결성 보장 필요
		for (int i = 0; i < 6; i++)
		{
			if (!bIsSubmissionDone[i]) 
			{
				if (i < 4) Arbiter->SignDisplayControllables[i]->SetStatus_Implementation(false);
			}
			else Arbiter->SubGuideControllables[i]->SetStatus_Implementation(false);
		}

		bInitializeFlag = true;
	}
}