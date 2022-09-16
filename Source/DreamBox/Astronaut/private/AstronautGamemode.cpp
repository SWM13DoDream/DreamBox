// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/AstronautGamemode.h"
#include "../public/MissionWidget.h"
#include "../public/TimerWidget.h"
#include "../public/GamemodeArbiter.h"
#include "../public/AstronautCharacter.h"

void AAstronautGamemode::BeginPlay() 
{
	Super::BeginPlay();

	// ���� �̼� ���� ���� �ʱ�ȭ (���� �̼��� InitializeMissions���� ó��)
	bIsMissionDone = false;
	MainMissionText = MAIN_MISSION_INIT;

	// 1�ʿ� �� ���� ȣ��Ǵ� Ÿ�̸Ӹ� ����. �ʱⰪ���� ����
	Time = TIME_PERIOD;
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AAstronautGamemode::HandleTimer, 1.0f, true, 1.0f);

	bInitializeFlag = false;
}

void AAstronautGamemode::InitializeMissions()
{
	// 6�� �ɼ� �� 3���� �����ϴ� ���� ������ ��� (ex. 7 = 000111, 11 = 001011, 13 = 001101 ... ) 
	int32 RandomMissionIndices[] = { 7, 11, 13, 14, 19, 21, 22, 25, 26, 28, 35, 37, 38, 41, 42, 44, 49, 50, 52, 56 };
	int32 RandomMissionSelector = RandomMissionIndices[FMath::RandRange(0, 19)];

	// ���� �����ڿ� ���� bool[SUBMISSION_NUM] Ÿ���� bIsSubmissionDone�� �ʱ�ȭ �� �Ҵ�
	for (int i = 0; i < SUBMISSION_NUM; i++)
	{
		if (RandomMissionSelector % 2 == 1)
		{
			bIsSubmissionDone[i] = true;

			// UnsetSubMission(i)�� ���� �ʰ� true ���ڸ� ���� ������ ���
			// true ���ڸ� interactiontrigger�� �ѱ�� ���� ���� �ÿ� �߻��ϴ� ���Ἲ ������ �ذ� ����
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

	// �̼� ���� ���÷��� ������Ʈ
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

	// �̼� ���� ���÷��� ������Ʈ
	CharacterMissionController->UpdateSubMissionDisplay();

	// ���̵� ���� Visibility ����
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

	// ù Ÿ�̸� tick���� ȣ�� (���Ἲ�� ����� Initialize Logic)
	if (!bInitializeFlag)
	{
		CharacterMissionController->UpdateMainMissionDisplay();
		CharacterMissionController->UpdateSubMissionDisplay();

		// SignDisplay ������ ��� widget �ʱ� ������ Ÿ�̹��� ���� ���� �� �־� ���Ἲ ���� �ʿ�
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