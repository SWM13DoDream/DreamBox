// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/SignDisplay.h"
#include "Components/WidgetComponent.h"
#include "../public/SignWidget.h"

// Sets default values
ASignDisplay::ASignDisplay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WIDGET"));
	WidgetComponent->SetupAttachment(RootComponent);

	bIsStable = true;
}

// Called when the game starts or when spawned
void ASignDisplay::BeginPlay()
{
	Super::BeginPlay();
	
	// 미리 캐스팅된 주요 제어 변수를 저장
	Widget = Cast<USignWidget>(WidgetComponent->GetWidget());

	// 이후 파생 BP에서 구현된 초기화 함수 호출 (DataTable 연동 등)
	Initialize();
}

void ASignDisplay::SetSignContent(FSignStruct Value) 
{
	Widget->SetIdentity(Value);
}

void ASignDisplay::SetStability(bool Value)
{
	bIsStable = Value;
	Widget->SetStateDisplay(bIsStable);
}

void ASignDisplay::SetStatus_Implementation(bool Value)
{
	SetStability(Value);
}