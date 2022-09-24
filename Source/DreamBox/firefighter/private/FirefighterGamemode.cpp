// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/FirefighterGamemode.h"
#include "../public/FirefighterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void AFirefighterGamemode::BeginPlay()
{
	Super::BeginPlay();

	//플레이어 캐릭터 레퍼런스 초기화 및 이벤트 바인딩
	if (GetWorld())
	{
		PlayerCharacterRef = Cast<AFirefighterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		PlayerCharacterRef->SetCharacterVisibility(false);
		CrossFadeAnimationEvent.AddDynamic(this, &AFirefighterGamemode::PlayCrossFadeAnim);
	}
}

void AFirefighterGamemode::BeginPlayAfterLoading(int32 PlayerID)
{
	Super::BeginPlayAfterLoading(PlayerID);

	//	PlayCrossFadeAnim(PlayerID);
	PlayerCharacterRef->SetCharacterVisibility(true);
	PlayerCharacterRef->SetActorLocation(FVector(52.0f, -372.f, 100.0f));
	PlayerCharacterRef->AddActorWorldRotation({ 0.0f, -90.0f, 0.0f });
	ShowInitialScript();
}

void AFirefighterGamemode::AddToCompleteSet(int32 MissionID)
{
	if (CompleteMissionSet.Contains(MissionID)) return;
	CompleteMissionSet.Add(MissionID);
}

bool AFirefighterGamemode::GetMissionIsComplete(int32 MissionID)
{
	return CompleteMissionSet.Contains(MissionID);
}

void AFirefighterGamemode::ShowInitialScript()
{
	if (!bShowInitScript) return;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
		ShowScriptWithID.Broadcast(0, InitialScriptID);
	}), 0.5f, false);
}

void AFirefighterGamemode::PlayCrossFadeAnim(int32 PlayerID)
{
	Super::PlayCrossFadeAnim(PlayerID);
	/* -- 플레이어 ID에 따라 구분할 로직이 들어갈 자리 -- */

	if (IsValid(PlayerCharacterRef))
	{
		PlayerCharacterRef->GetCharacterMovement()->Deactivate();
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			PlayerCharacterRef->GetCharacterMovement()->Activate();
		}), 1.25f, false);
	}
}
