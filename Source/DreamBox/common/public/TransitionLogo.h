// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "TransitionLogo.generated.h"

/*
 - Name        : ATransitionLogo
 - Description : Transition Logo Ŭ����, �ΰ� �ִϸ��̼� ���� ����
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
	//�ΰ� �ִϸ��̼��� ���
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayLogoAnimation(bool bIsBeginAnim);

	//�ΰ� ������� �ִϸ��̼� ���
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayLogoDisappearAnim();

	//�ΰ� �ִϸ��̼� �ɼ��� �����ִ��� ��ȯ
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool GetLogoAnimationIsSet(bool bIsBeginAnim);
	
	//�ִϸ��̼��� ����ϰ� ������ �ε��� ����
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
