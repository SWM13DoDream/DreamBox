// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/InteractionTrigger.h"
#include "../public/AstronautGamemode.h"
#include "../public/InteractionWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractionTrigger::AInteractionTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WidgetComponent = CreateDefaultSubobject<class UWidgetComponent>(TEXT("WIDGET"));
	WidgetComponent->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX_COLLISION"));
	BoxCollision->SetupAttachment(RootComponent);

	bIsInteractable = true;
	bIsAvailable = false;
}

// Called when the game starts or when spawned
void AInteractionTrigger::BeginPlay()
{
	Super::BeginPlay();

	// 미리 캐스팅된 주요 제어 변수를 저장
	Widget = Cast<UInteractionWidget>(WidgetComponent->GetWidget());
	Gamemode = Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));

	InitializeMode();
}

void AInteractionTrigger::SetInteractionContent(FInteractionStruct Content)
{
	Widget->SetIdentity(this, Content);
}

void AInteractionTrigger::OnTriggerEnter(class AActor* OtherActor)
{
	if (bIsInteractable && IsValidPlayer(OtherActor))
	{
		if (bHasVariableMode)
		{
			if (Gamemode->bIsMissionDone)
			{
				if (Gamemode->IsAboardable())
				{
					FString NewMode = "FinishMission";
					InteractionMode = FName(*NewMode);
					InitializeMode();
				}
				else
				{
					FString NewMode = "TimeNotMatch";
					InteractionMode = FName(*NewMode);
					InitializeMode();
				}
			}
		}
		Widget->Animate(true);
		bIsAvailable = true;
	}
}

void AInteractionTrigger::OnTriggerExit(class AActor* OtherActor)
{
	if (bIsInteractable && IsValidPlayer(OtherActor))
	{
		Widget->Animate(false);
		bIsAvailable = false;
	}
}

void AInteractionTrigger::OnInteract()
{
	if (bIsInteractable && bIsAvailable)
	{
		FString InteractionKey = InteractionMode.ToString();
		if (InteractionKey.Equals(TEXT("ExitVehicle")))
		{
			Gamemode->PlayCrossFade();

			GetWorld()->GetTimerManager().SetTimer(DelayHandler, FTimerDelegate::CreateLambda([&]()
			{
				Gamemode->MoveLEM(false);

				// 핸들러 초기화
				GetWorld()->GetTimerManager().ClearTimer(DelayHandler);
			}), 1.0f, false);
		}
		else if (InteractionKey.Equals(TEXT("EnterVehicle")))
		{
			Gamemode->PlayCrossFade();

			GetWorld()->GetTimerManager().SetTimer(DelayHandler, FTimerDelegate::CreateLambda([&]()
			{
				Gamemode->MoveLEM(true);

				// 핸들러 초기화
				GetWorld()->GetTimerManager().ClearTimer(DelayHandler);
			}), 1.0f, false);
		}
		else if (InteractionKey.Equals(TEXT("Install")))
		{
			Gamemode->DoMainMission();
		}
		else if (InteractionKey.Equals(TEXT("MissionPlant")))
		{
			Gamemode->DoSubMission(0);
		}
		else if (InteractionKey.Equals(TEXT("MissionCrew")))
		{
			Gamemode->DoSubMission(1);
		}
		else if (InteractionKey.Equals(TEXT("MissionLaboratory")))
		{
			Gamemode->DoSubMission(2);
		}
		else if (InteractionKey.Equals(TEXT("MissionSilo")))
		{
			Gamemode->DoSubMission(3);
		}
		else if (InteractionKey.Equals(TEXT("MissionRock")))
		{
			Gamemode->DoSubMission(4);
		}
		else if (InteractionKey.Equals(TEXT("MissionRobot")))
		{
			Gamemode->DoSubMission(5);
		}
	}
}

void AInteractionTrigger::Unset()
{
	bIsInteractable = false;
	bIsAvailable = false;
}

bool AInteractionTrigger::IsValidPlayer(class AActor* TargetActor)
{
	FString PlayerTag = "Player";
	return ((TargetActor->Tags).IsValidIndex(0) && (TargetActor->Tags)[0] == FName(*PlayerTag));
}

void AInteractionTrigger::SetStatus_Implementation(bool Value)
{
	// Value = true인 경우 무결성 보장 (게임 시작 시, Widget->Animate 호출하지 않음)
	Unset();
	if (!Value) Widget->Animate(false);
}