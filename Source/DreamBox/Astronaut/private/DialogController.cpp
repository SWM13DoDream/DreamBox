// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/DialogController.h"
#include "../public/DialogWidget.h"
#include "../public/AstronautCharacter.h"
#include "../public/AstronautGamemode.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADialogController::ADialogController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGET"));
	WidgetComponent->SetupAttachment(RootComponent);

	DialogState = 0;
	bMultiplayDialogFlag = false;
	bDialogLock = false;
	bDoneMessageRegistered = false;
}

// Called when the game starts or when spawned
void ADialogController::BeginPlay()
{
	Super::BeginPlay();

	// 미리 캐스팅된 주요 제어 변수를 저장
	Widget = Cast<UDialogWidget>(WidgetComponent->GetWidget());
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player->IsLocallyControlled()) LocalPlayer = Cast<AAstronautCharacter>(Player);
	else
	{
		Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);
		LocalPlayer = Cast<AAstronautCharacter>(Player);
	}
}

void ADialogController::SetActivated(bool bValue, int32 SelectedMission, bool bMultiplay)
{
	Mission = SelectedMission;
	bInMultiplay = bMultiplay;

	if (bValue)
	{
		// 타이머에 UpdateState 연동
		GetWorldTimerManager().SetTimer(UpdateStateHandler, this, &ADialogController::UpdateState, 1.0f, true, 1.0f);

		if (Mission == EAstronautMissionType::LEM)
		{
			// 미션 시작 시점에 다이얼로그 출력
			LEMDialogIntro();
		}
		else if (Mission == EAstronautMissionType::CSM)
		{
			// 미션 시작 시점에 다이얼로그 출력
			CSMDialogIntro();
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(UpdateStateHandler);
	}
}

// 타이머에 bind되어 호출되는 업데이트 함수 (expected: one invocation per second)
void ADialogController::UpdateState()
{
	int32 Time = LocalPlayer->Time;
	if (Mission == EAstronautMissionType::LEM)
	{
		if (DialogState == 0 && Time < 150 && Time > 0)
		{
			DialogState = 1;
			LEMDialogMid();
		}
		else if (DialogState == 1 && Time < 30)
		{
			DialogState = 2;
			LEMDialogApprox();
		}
		else if (DialogState == 2 && Time > 150)
		{
			DialogState = 0;
		}
	}
	else if (Mission == EAstronautMissionType::CSM)
	{
		if (DialogState == 0 && Time < 100) {
			DialogState = 1;
			CSMDialogMid();
		}
		else if (DialogState == 1 && Time > 100)
		{
			DialogState = 0;
		}
	}
}

void ADialogController::AnnounceMissionDoneFromOther()
{
	if (Mission == EAstronautMissionType::LEM)
	{
		if (bDialogLock) bDoneMessageRegistered = true;
		else LEMDoneMessageFromCSM();
	}
	else if (Mission == EAstronautMissionType::CSM)
	{
		if (bDialogLock) bDoneMessageRegistered = true;
		else CSMDoneMessageFromLEM();
	}
}

void ADialogController::SetDialogContent(FText Value)
{
	Widget->SetIdentity(Value);
}