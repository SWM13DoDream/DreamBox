// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "TransitionStructBase.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

/*
 - Name        : AVRCharacter
 - Descirption : 메인 Playable VR 캐릭터 Base
 - Date        : 2022/09/27 LJH
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

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION(Client, Reliable)
		virtual void OnRPCStartContent(int32 PlayerID, FContentStartInfo StartInfo);

	UFUNCTION(Server, Reliable)
		virtual void MakeRPCInitPlayerTransform(FTransform InitialTransform);

	UFUNCTION(NetMulticast, Reliable)
		virtual void OnRPCInitPlayerTransform(FTransform InitialTransform);

public:
	//기본 이동 함수 : 앞뒤 이동
	UFUNCTION()
		void MoveForward(float Value);

	//기본 이동 함수 : 양옆 이동
	UFUNCTION()
		void MoveRight(float Value);

	//기본 회전 함수 : 45도 만큼 카메라 전환
	UFUNCTION()
		void SnapTurn(float Value);

	//SnapTurn이 연속으로 입력되는 것을 방지하는 함수
	UFUNCTION()
		void ResetSnapTurnControllerInput();

	//크로스 페이드를 실제로 출력하는 로직, 각 자식 게임모드 클래스에서 바인딩 해야함
	//PlayerID 미사용 파라미터 제거 예정
	UFUNCTION(BlueprintCallable)
		void PlayCrossFadeAnim();

	
	UFUNCTION()
		virtual void InitLevelSequence();

	//Jump를 활성화/비활성화 함
	UFUNCTION()
		void SetCanJump(bool NewState);

	UFUNCTION()
		void InitGameModeRef();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//VR Immersive 에셋 사용을 위한 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* VROrigin;

	//캐릭터의 메인 카메라 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* FollowingCamera;

	//VR Immersive 에셋 사용을 위한 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* SpectatorRef;

	//VR Immersive 에셋 사용을 위한 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* GenericHMD;

	//VR Immersive 에셋 사용을 위한 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* HeadCollision;

	//VR Immersive 에셋 사용을 위한 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetInteractionComponent* WidgetInteraction;


//=============== 컴포넌트가 아닌 멤버 ======================
public:
	//크로스 페이드 효과 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* CrossFadeSequence;

	//C++ 딜레이 사용 위한 타이머 핸들 
	UPROPERTY()
		struct FTimerHandle WaitHandle;

	//점프가 가능한지? (BP에서 옵션 지정, 기본값 : t)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
		bool bCanJump = true; 

private:
	//SnapTurn 실행이 끝났는지? (연속 입력 방지)
	UPROPERTY()
		bool bSnapTurnIsFinished;

	UPROPERTY()
		int32 PlayerControllerID;

	//시퀀스 플레이어 (FadeIn & Out)
	UPROPERTY()
		class ULevelSequencePlayer* CrossFadePlayer;

	UPROPERTY()
		class ADreamBoxGameModeBase* GamemodeRef; 

};
