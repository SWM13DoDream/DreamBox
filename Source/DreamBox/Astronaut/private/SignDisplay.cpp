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
	
	// �̸� ĳ���õ� �ֿ� ���� ������ ����
	Widget = Cast<USignWidget>(WidgetComponent->GetWidget());

	// ���� �Ļ� BP���� ������ �ʱ�ȭ �Լ� ȣ�� (DataTable ���� ��)
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