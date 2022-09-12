// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "UObject/Interface.h"
#include "AstronautControllableInterface.generated.h"

/*
 - Name        : UAstronautControllableInterface
 - Description : 우주 비행사 컨텐츠의 게임모드에 의해 관리 가능한 클래스에 활용되는 인터페이스
 - Date        : 2022/09/03 DEVroar
*/

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAstronautControllableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DREAMBOX_API IAstronautControllableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface")
		void SetStatus(bool Value);
};
