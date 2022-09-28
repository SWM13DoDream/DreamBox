// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "TransitionLogo.generated.h"

/*
 - Name        : ATransitionLogo
 - Description : Transition Logo 클래스, 로고 애니메이션 로직 포함
 - Date        : 2022/09/28 LJH
*/

UCLASS()
class DREAMBOX_API ATransitionLogo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransitionLogo();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//로고 애니메이션을 출력
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayLogoAnimation(bool bIsBeginAnim);

	//로고가 사라지는 애니메이션 출력
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayLogoDisappearAnim();

	//로고 애니메이션 옵션이 켜져있는지 반환
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool GetLogoAnimationIsSet(bool bIsBeginAnim);
	
	//애니메이션을 출력하고 레벨의 로딩을 시작
	UFUNCTION()
		void StartLoadTargetMap();

public:
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UWidgetComponent* LogoWidgetComponent;

private:
	UPROPERTY()
		class APersistentLevelBase* LevelScriptRef;

	UPROPERTY()
		struct FTimerHandle WaitHandle;
};
