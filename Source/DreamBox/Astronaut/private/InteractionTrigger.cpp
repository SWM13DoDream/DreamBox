// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/InteractionTrigger.h"
#include "../public/InteractionWidget.h"
#include "../public/AstronautCharacter.h"
#include "../public/AstronautGamemode.h"
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
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player->IsLocallyControlled()) LocalPlayer = Cast<AAstronautCharacter>(Player);
	else
	{
		Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);
		LocalPlayer = Cast<AAstronautCharacter>(Player);
	}

	InitializeMode();
}

void AInteractionTrigger::SetInteractionContent(FInteractionStruct Content)
{
	Widget->SetIdentity(this, Content);
}

void AInteractionTrigger::OnTriggerEnter(class AActor* OtherActor)
{
	if (IsValidPlayer(OtherActor))
	{
		if (bHasVariableMode)
		{
			if (LocalPlayer->bIsMissionDone)
			{
				if (LocalPlayer->IsAboardable())
				{
					FString NewMode = "FinishMission";
					InteractionMode = FName(*NewMode);
					InitializeMode();
					if (!bIsInteractable) bIsInteractable = true;
				}
				else
				{
					FString NewMode = "TimeNotMatch";
					InteractionMode = FName(*NewMode);
					InitializeMode();
				}
			}
		}

		if (bIsInteractable)
		{
			FString InteractionKey = InteractionMode.ToString();
			if (InteractionKey.Equals(TEXT("FinishCSM")))
			{
				if (!LocalPlayer->bIsMissionDone) return;
			}
			else if (InteractionKey.Equals(TEXT("EnterGateway")))
			{
				if (!LocalPlayer->bIsMissionDone) return;
			}

			Widget->Animate(true);
			bIsAvailable = true;
		}
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
			LocalPlayer->PlayCrossFade();

			GetWorld()->GetTimerManager().SetTimer(DelayHandler, FTimerDelegate::CreateLambda([&]()
			{
				LocalPlayer->MoveLEM(false);

				// 핸들러 초기화
				GetWorld()->GetTimerManager().ClearTimer(DelayHandler);
			}), 1.0f, false);
		}
		else if (InteractionKey.Equals(TEXT("EnterVehicle")))
		{
			LocalPlayer->PlayCrossFade();

			GetWorld()->GetTimerManager().SetTimer(DelayHandler, FTimerDelegate::CreateLambda([&]()
			{
				LocalPlayer->MoveLEM(true);

				// 핸들러 초기화
				GetWorld()->GetTimerManager().ClearTimer(DelayHandler);
			}), 1.0f, false);
		}
		else if (InteractionKey.Equals(TEXT("Install")))
		{
			LocalPlayer->DoMainMission();
		}
		else if (InteractionKey.Equals(TEXT("MissionPlant")))
		{
			LocalPlayer->DoSubMission(0);
		}
		else if (InteractionKey.Equals(TEXT("MissionCrew")))
		{
			LocalPlayer->DoSubMission(1);
		}
		else if (InteractionKey.Equals(TEXT("MissionLaboratory")))
		{
			LocalPlayer->DoSubMission(2);
		}
		else if (InteractionKey.Equals(TEXT("MissionSilo")))
		{
			LocalPlayer->DoSubMission(3);
		}
		else if (InteractionKey.Equals(TEXT("MissionRock")))
		{
			LocalPlayer->DoSubMission(4);
		}
		else if (InteractionKey.Equals(TEXT("MissionRobot")))
		{
			LocalPlayer->DoSubMission(5);
		}
		else if (InteractionKey.Equals(TEXT("ExitGateway")))
		{
			Unset();
			Widget->Animate(false);
			LocalPlayer->PlayCrossFade();
			GetWorld()->GetTimerManager().SetTimer(DelayHandler, FTimerDelegate::CreateLambda([&]()
			{
				LocalPlayer->StartEVA();

				// 핸들러 초기화
				GetWorld()->GetTimerManager().ClearTimer(DelayHandler);
			}), 1.0f, false);
		}
		else if (InteractionKey.Equals(TEXT("Adjust")))
		{
			LocalPlayer->DoMainMission();
			Widget->Animate(false);
			Unset();

			LocalPlayer->PlayCrossFade();

			GetWorld()->GetTimerManager().SetTimer(DelayHandler, FTimerDelegate::CreateLambda([&]()
			{
				LocalPlayer->ReturnIVA();

				// 핸들러 초기화
				GetWorld()->GetTimerManager().ClearTimer(DelayHandler);
			}), 1.0f, false);
		}
		else if (InteractionKey.Equals(TEXT("EnterGateway")))
		{
			Unset();
			LocalPlayer->PlayCrossFade();

			GetWorld()->GetTimerManager().SetTimer(DelayHandler, FTimerDelegate::CreateLambda([&]()
			{
				LocalPlayer->ReturnIVA();

				// 핸들러 초기화
				GetWorld()->GetTimerManager().ClearTimer(DelayHandler);
			}), 1.0f, false);
		}
		else if (InteractionKey.Equals(TEXT("TimeNotMatch")))
		{
			// Multiplay 여부 체크
			ENetMode NetworkingMode = GetWorld()->GetNetMode();
			bool bInMultiplay = false;
			if (NetworkingMode == NM_ListenServer)
			{
				AAstronautGamemode* Gamemode =
					Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
				if (Gamemode->RemotePlayer != nullptr) bInMultiplay = true;
			}
			else if (NetworkingMode == NM_Client) bInMultiplay = true;

			if (bInMultiplay)
			{
				Unset();
				Widget->Animate(false);
				LocalPlayer->MakeRPCMissionDone();
			}
		}
		else if (InteractionKey.Equals(TEXT("FinishCSM")))
		{
			Unset();
			Widget->Animate(false);

			// Multiplay 여부 체크
			ENetMode NetworkingMode = GetWorld()->GetNetMode();
			bool bInMultiplay = false;
			if (NetworkingMode == NM_ListenServer)
			{
				AAstronautGamemode* Gamemode =
					Cast<AAstronautGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
				if (Gamemode->RemotePlayer != nullptr) bInMultiplay = true;
			}
			else if (NetworkingMode == NM_Client) bInMultiplay = true;

			if (bInMultiplay) LocalPlayer->MakeRPCMissionDone();
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