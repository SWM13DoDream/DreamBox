// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautControllableInterface.h"
#include "GamemodeArbiter.generated.h"

/*
 - Name        : AGamemodeArbiter
 - Description : Map에 배치되어 게임 로직 - 아웃라이너 액터들을 중계하는 C++ 액터
 - Caution     : AstronautGamemode가 아니라 AstronautCharacter에서 관리됨. (멀티플레이)
 - Date        : 2022/09/03 DEVroar
*/

UCLASS()
class DREAMBOX_API AGamemodeArbiter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamemodeArbiter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Gamemode에서 제어하는 SignDisplay 액터 오브젝트 레퍼런스 배열
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SignDisplayControllables;

	// Gamemode에서 제어하는 InteractionTrigger 액터 오브젝트 레퍼런스 (메인 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainInteractionControllable;

	// Gamemode에서 제어하는 InteractionTrigger 액터 오브젝트 레퍼런스 배열 (서브 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubInteractionControllables;

	// Gamemode에서 제어하는 ControllableStaticMesh 액터 오브젝트 레퍼런스 (메인 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainStaticMeshControllable;

	// Gamemode에서 제어하는 ControllableStaticMesh 액터 오브젝트 레퍼런스 배열 (서브 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubStaticMeshControllables;

	// Gamemode에서 제어하는 Destination Guide 액터 오브젝트 레퍼런스 (메인 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainGuideControllable;

	// Gamemode에서 제어하는 Destination Guide 액터 오브젝트 레퍼런스 배열 (서브 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubGuideControllables;

public:
	// 미션 위젯 표시 TEXT 상수값. 역시 뷰포트에서 기본값 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText MAIN_MISSION_INIT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText MAIN_MISSION_DONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		TArray<FText> SUB_MISSION_TEXT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText SUB_MISSION_DONE;
};
