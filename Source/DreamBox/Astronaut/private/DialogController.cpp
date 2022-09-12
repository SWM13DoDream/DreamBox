// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/DialogController.h"
#include "../public/DialogWidget.h"
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
}

// Called when the game starts or when spawned
void ADialogController::BeginPlay()
{
	Super::BeginPlay();

	// 미리 캐스팅된 주요 제어 변수를 저장
	Widget = Cast<UDialogWidget>(WidgetComponent->GetWidget());
	Gamemode = Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

	// 타이머에 UpdateState 연동
	GetWorldTimerManager().SetTimer(UpdateStateHandler, this, &ADialogController::UpdateState, 1.0f, true, 1.0f);
	
	// 게임 시작 시 다이얼로그 출력
	LEMDialogIntro();
}

// 타이머에 bind되어 호출되는 업데이트 함수 (expected: one invocation per second)
void ADialogController::UpdateState()
{
	int32 Time = Gamemode->Time;
	if (DialogState == 0 && Time < 150)
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

void ADialogController::SetDialogContent(FText Value)
{
	Widget->SetIdentity(Value);
}