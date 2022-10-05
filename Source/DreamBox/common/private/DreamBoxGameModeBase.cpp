// Copyright Epic Games, Inc. All Rights Reserved.


#include "../public/DreamBoxGameModeBase.h"
#include "../public/VRCharacter.h"
#include "../public/PersistentLevelBase.h"
#include "Kismet/GameplayStatics.h"

void ADreamBoxGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	bUseSeamlessTravel = true;
}

void ADreamBoxGameModeBase::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);

	if (IsValid(NewPlayerController))
	{
		int32 newPlayerIdx = PlayerControllerList.Num();
		PlayerControllerList.Add(NewPlayerController);
		PlayerCharacterList.Add(Cast<AVRCharacter>(NewPlayerController->GetCharacter()));
		PlayerCharacterList[newPlayerIdx]->GetCharacterMovement()->Deactivate();
		PlayerLoadStateList.Add(false);
		if (CurrentLoadState == EPersistentLoadStateType::E_PostLoad)
		{
			PreLoadingEndEvent();
			PostLoadingEvent();
		}
	}
}

void ADreamBoxGameModeBase::PreLoadingEndEvent()
{
	for (int32 playerIdx = 0; playerIdx < GetPlayerControllerCount(); playerIdx++)
	{
		AVRCharacter* playerRef = GetPlayerCharacterList()[playerIdx];
		if (IsValid(playerRef) && !PlayerLoadStateList[playerIdx]
			&& ContentStartInfoList.IsValidIndex(playerIdx))
		{
			playerRef->OnRPCSetupContent(playerIdx, GetPlayerStartInfo(playerIdx));
			playerRef->PlayLevelInitSequence();
		}
	}
}

void ADreamBoxGameModeBase::PostLoadingEvent()
{
	for (int32 playerIdx = 0; playerIdx < GetPlayerControllerCount(); playerIdx++)
	{
		AVRCharacter* playerRef = GetPlayerCharacterList()[playerIdx];
		if (IsValid(playerRef) && !PlayerLoadStateList[playerIdx]
			&& ContentStartInfoList.IsValidIndex(playerIdx))
		{
			playerRef->OnRPCStartContent(playerIdx);
			playerRef->GetCharacterMovement()->Activate(true);
			PlayerLoadStateList[playerIdx] = true;
		}
	}
}

void ADreamBoxGameModeBase::InitLevelScriptRef(APersistentLevelBase* NewScriptRef)
{
	if (IsValid(NewScriptRef))
	{
		DebugMessage(100.0f);
		LevelScriptRef = NewScriptRef;
		LevelScriptRef->PreLoadingEndDelegate.AddDynamic(this, &ADreamBoxGameModeBase::PreLoadingEndEvent);
		LevelScriptRef->PostLoadingDelegate.AddDynamic(this, &ADreamBoxGameModeBase::PostLoadingEvent);
	}
}

FContentStartInfo ADreamBoxGameModeBase::GetPlayerStartInfo(int32 PlayerID)
{
	if (ContentStartInfoList.IsValidIndex(PlayerID))
	{
		return ContentStartInfoList[PlayerID];
	}
	return FContentStartInfo();
}


/*

1. 로딩 이후 
    - 캐릭터 이동
	- 멀티플레이 대응
2. CrossFade 이벤트
    - Play initial anim 옵션 ? -> GM없는 클라에서도 get하도록?

*/