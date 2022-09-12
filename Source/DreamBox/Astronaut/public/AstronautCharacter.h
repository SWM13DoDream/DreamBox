// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/VRCharacter.h"
#include "AstronautCharacter.generated.h"

/*
 - Name			: AAstronautCharacter
 - Author		: DEVroar
 - Descirption	: 우주비행사 Default Pawn (플레이어 캐릭터)
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

	// 인터렉션 키 Press에 바인딩
	UFUNCTION()
		void OnInteract();

	// 인터렉션 키 Release에 바인딩
	UFUNCTION()
		void ReleaseInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 캐릭터 VR Origin에 부착되는 타이머 표시 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* TimerWidget;

	// 캐릭터 VR Origin에 부착되는 미션 표시 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionWidget;
};