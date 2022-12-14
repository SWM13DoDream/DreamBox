// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/VRCharacter.h"
#include "LobbyCharacter.generated.h"

/*
 - Name        : ALobbyCharacter
 - Descirption : Lobby ???????? ???? Playable ĳ????
 - Date        : 2022/10/04 LJH
*/

UCLASS()
class DREAMBOX_API ALobbyCharacter : public AVRCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALobbyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//???? ???????? ?ʱ?ȭ
	virtual void InitLevelSequence() override;

	virtual void OnRPCStartContent(int32 PlayerID) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
