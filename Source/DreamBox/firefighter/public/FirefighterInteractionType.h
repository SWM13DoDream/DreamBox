// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../../common/public/DreamBox.h"
#include "FirefighterInteractionType.generated.h"

/*
 - Name        : EFirefighterInteractionType
 - Descirption : Firefighter �������� ���ͷ��� ����
 - Date        : 2022/09/02 LJH
*/

UENUM(BlueprintType)
enum class EFirefighterInteractionType : uint8
{
	E_NONE = 0		UMETA(DisplayName = "None"),
	E_CARRY			UMETA(DisplayName = "Carry"),
	E_PICK			UMETA(DisplayName = "Pick"),
	E_INVESTIGATE	UMETA(DisplayName = "Investigate")
};