// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/AstronautGamemode.h"
#include "../public/AstronautCharacter.h"
#include "../public/GamemodeArbiter.h"
#include "SocketSubsystem.h"

void AAstronautGamemode::BeginPlay() 
{
	Super::BeginPlay();

	bInMission = false;
	HostMission = EAstronautMissionType::NONE;
	ClientMission = EAstronautMissionType::NONE;

	NetworkingStatus = GetWorld()->GetNetMode();
}

void AAstronautGamemode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	// �̹� ����Ʈ �÷��̾� �� ���� �����ϰ� �ְų� �̼ǿ� ������ ��� �ܺ� ���� ����
	if (NetworkingStatus == ENetMode::NM_ListenServer)
	{
		if (RemotePlayer != nullptr)
		{
			ErrorMessage = "Too many players in the content.";
		}
		if (bInMission)
		{
			ErrorMessage = "The content has already started in place";
		}
	}
}

void AAstronautGamemode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// ȣ��Ʈ �÷��̾�
	if (LocalPlayer == nullptr)
	{
		LocalPlayer = Cast<AAstronautCharacter>(NewPlayer->GetPawn());
		//LocalPlayer->OnRPCStartContent(0);
	}
	// ����Ʈ �÷��̾�
	else if (RemotePlayer == nullptr)
	{
		RemotePlayer = Cast<AAstronautCharacter>(NewPlayer->GetPawn());
		//RemotePlayer->OnRPCStartContent(1);

		if (!bInMission)
		{
			LocalPlayer->CloseWaitingPanel();
		}
	}
}

void AAstronautGamemode::PreLoadingEndEvent()
{
	Super::PreLoadingEndEvent();
}

void AAstronautGamemode::PostLoadingEvent()
{
	Super::PostLoadingEvent();
}

void AAstronautGamemode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	// TODO
}

FString AAstronautGamemode::GetIPAddr()
{
	FString IpAddr("NONE");
	bool bBindable = false;
	TSharedRef<FInternetAddr> LocalIP =
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bBindable);

	if (LocalIP->IsValid()) IpAddr = LocalIP->ToString(false);
	return IpAddr;
}