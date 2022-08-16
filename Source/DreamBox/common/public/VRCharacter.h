// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

/*
 - Name        : AVRCharacter
 - Descirption : 메인 Playable VR 캐릭터 Base
 - Date        : 2022/08/16 LJH
*/

UCLASS()
class DREAMBOX_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//기본 이동 함수 : 앞뒤 이동
	UFUNCTION()
		void MoveForward(float Value);

	//기본 이동 함수 : 양옆 이동
	UFUNCTION()
		void MoveRight(float Value);

	//기본 회전 함수 : 오른쪽으로 45도 만큼 카메라 전환
	UFUNCTION()
		void SnapTurnLeft();

	//기본 회전 함수 : 오른쪽으로 45도 만큼 카메라 전환
	UFUNCTION()
		void SnapTurnRight();

	//SnapTurn이 연속으로 입력되는 것을 방지하는 함수
	UFUNCTION()
		void ResetSnapTurn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//VR Immersive 에셋 사용을 위한 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* VROrigin;

	//VR Immersive 에셋 사용을 위한 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* SpectatorRef;

	//캐릭터의 메인 카메라 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* FollowingCamera;

private:
	//SnapTurn 실행이 끝났는지? (연속 입력 방지)
	UPROPERTY()
		bool bSnapTurnIsFinished;
};
