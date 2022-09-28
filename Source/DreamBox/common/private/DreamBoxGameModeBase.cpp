// Copyright Epic Games, Inc. All Rights Reserved.


#include "../public/DreamBoxGameModeBase.h"
#include "../public/VRCharacter.h"
#include "Kismet/GameplayStatics.h"

void ADreamBoxGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AfterLoadingEvent.AddDynamic(this, &ADreamBoxGameModeBase::BeginPlayAfterLoading);
}

void ADreamBoxGameModeBase::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);

	PlayerControllerList.Add(NewPlayerController);
	PlayerCharacterList.Add(Cast<AVRCharacter>(NewPlayerController->GetCharacter()));
}

void ADreamBoxGameModeBase::BeginPlayAfterLoading()
{
	for (int32 playerIdx = 0; playerIdx < PlayerCharacterList.Num(); playerIdx++)
	{
		AVRCharacter* playerRef = PlayerCharacterList[playerIdx];
		if (IsValid(playerRef)
			&& ContentStartInfoList.IsValidIndex(playerIdx))
		{
			playerRef->OnRPCStartContent(playerIdx, ContentStartInfoList[playerIdx]);
		}
	}
}

/*

1. �ε� ���� 
    - ĳ���� �̵�
	- ��Ƽ�÷��� ����
2. CrossFade �̺�Ʈ
    - Play initial anim �ɼ� ? -> GM���� Ŭ�󿡼��� get�ϵ���?

*/