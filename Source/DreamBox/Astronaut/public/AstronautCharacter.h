// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/VRCharacter.h"
#include "AstronautCharacter.generated.h"

/*
 - Name			: AAstronautCharacter
 - Author		: DEVroar
 - Descirption	: ���ֺ���� Default Pawn (�÷��̾� ĳ����)
 - Date			: 2022/07/26
*/

UCLASS()
class DREAMBOX_API AAstronautCharacter : public AVRCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAstronautCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	// ���ͷ��� Ű Press�� ���ε�
	UFUNCTION()
		void OnInteract();

	// ���ͷ��� Ű Release�� ���ε�
	UFUNCTION()
		void ReleaseInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// ĳ���� VR Origin�� �����Ǵ� Ÿ�̸� ǥ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* TimerWidget;

	// ĳ���� VR Origin�� �����Ǵ� �̼� ǥ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionWidget;
};