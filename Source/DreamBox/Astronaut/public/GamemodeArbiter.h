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
	// 월드 뷰포트 상의 MissionSelectionPanel 액터 오브젝트 레퍼런스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MissionSelectionControllable;

	// 월드 뷰포트 상의 SignDisplay 액터 오브젝트 레퍼런스 배열
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SignDisplayControllables;

	// 월드 뷰포트 상의 InteractionTrigger 액터 오브젝트 레퍼런스 (메인 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainInteractionControllable;

	// 월드 뷰포트 상의 InteractionTrigger 액터 오브젝트 레퍼런스 배열 (서브 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubInteractionControllables;

	// 월드 뷰포트 상의 ControllableStaticMesh 액터 오브젝트 레퍼런스 (메인 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainStaticMeshControllable;

	// 월드 뷰포트 상의 ControllableStaticMesh 액터 오브젝트 레퍼런스 배열 (서브 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubStaticMeshControllables;

	// 월드 뷰포트 상의 Destination Guide 액터 오브젝트 레퍼런스 (LEM 메인 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> MainGuideControllable;

	// 월드 뷰포트 상의 Destination Guide 액터 오브젝트 레퍼런스 배열 (LEM 서브 미션)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> SubGuideControllables;

	// 월드 뷰포트 상의 Destination Guide 액터 오브젝트 레퍼런스 배열 (CSM 선외 작업 전)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> BeforeEVAGuideControllables;

	// 월드 뷰포트 상의 Destination Guide 액터 오브젝트 레퍼런스 배열 (CSM 선외 작업 후)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> AfterEVAGuideControllables;

	// 월드 뷰포트 상의 EVA Destination Guide 액터 오브젝트 레퍼런스 (미션 수행 전)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> InEVADefaultControllables;

	// 월드 뷰포트 상의 EVA Destination Guide 액터 오브젝트 레퍼런스 (미션 수행 후)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TArray<TScriptInterface<class IAstronautControllableInterface>> InEVAEditControllables;

	// 월드 뷰포트 상의 왼손 GrabUserDisplay 액터 오브젝트 레퍼런스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> LeftGrabDisplayControllable;

	// 월드 뷰포트 상의 오른손 GrabUserDisplay 액터 오브젝트 레퍼런스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controllables")
		TScriptInterface<class IAstronautControllableInterface> RightGrabDisplayControllable;

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
