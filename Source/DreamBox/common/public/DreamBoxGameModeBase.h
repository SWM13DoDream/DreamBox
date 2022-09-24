// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../../common/public/DreamBox.h"
#include "GameFramework/GameModeBase.h"
#include "DreamBoxGameModeBase.generated.h"

/* 
 - Name        : ADreamBoxGamemode
 - Descirption : 메인 게임모드 베이스, 레벨 스트리밍 관련 로직이 들어있음
 - Date        : 2022/09/03 LJH
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleDynamicOneParam, int32, PlayerID);


UCLASS()
class DREAMBOX_API ADreamBoxGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	//로딩(콘텐츠 레벨 스트리밍)이 끝난 시점에 호출되는 이벤트 
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicOneParam LoadingEndEvent;

	//CrossFade 애니메이션을 출력
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicOneParam CrossFadeAnimationEvent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//로딩이 끝난 이후의 BeginPlay 이벤트
	UFUNCTION()
		virtual void BeginPlayAfterLoading(int32 PlayerID);

	//레벨 시퀀스를 초기화
	UFUNCTION()
		void InitLevelSequence();

	//크로스 페이드를 실제로 출력하는 로직, 각 자식 게임모드 클래스에서 바인딩 해야함
	UFUNCTION(BlueprintCallable)
		virtual void PlayCrossFadeAnim(int32 PlayerID);

public:
	//크로스 페이드 효과 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* CrossFade;

private:
	//시퀀스 플레이어
	UPROPERTY()
		class ULevelSequencePlayer* CrossFadePlayer;
};
