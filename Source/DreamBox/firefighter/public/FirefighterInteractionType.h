// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirefighterInteractionType.generated.h"

/*
 - Name        : EFirefighterInteractionType
 - Descirption : Firefighter 직업군의 인터렉션 종류
 - Date        : 2022/07/20 LJH
*/

UENUM(BlueprintType)
enum class EFirefighterInteractionType : uint8
{
	E_NONE = 0		UMETA(DisplayName = "None"),
	E_CARRY			UMETA(DisplayName = "Carry"),
	E_PICK			UMETA(DisplayName = "Pick"),
};