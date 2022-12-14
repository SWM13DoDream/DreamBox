// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "TransitionStructBase.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

/*
 - Name        : AVRCharacter
 - Descirption : 메인 Playable VR 캐릭터 Base
 - Date        : 2022/10/04 LJH
*/

UENUM(BlueprintType)
enum class EPlayerLevelSequenceType : uint8
{
	E_CrossFade	= 0		UMETA(DisplayName = "CrossFade"),
	E_FadeIn			UMETA(DisplayName = "FadeIn"),
	E_FadeOut			UMETA(DisplayName = "FadeOut")
};

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

///============================================
/// Replication, RPC 관련 함수
///============================================
public:	
	UFUNCTION(Client, Reliable)
		void OnRPCSetupContent(int32 PlayerID, FContentStartInfo StartInfo);
	
	//UFUNCTION(Client, Reliable)
		virtual void OnRPCStartContent(int32 PlayerID);
	
	UFUNCTION(Server, Reliable)
		virtual void MakeRPCInitPlayerTransform(FTransform InitialTransform);

	UFUNCTION(NetMulticast, Reliable)
		virtual void OnRPCInitPlayerTransform(FTransform InitialTransform);

///============================================
/// 기본적인 Movement 관련 함수
///============================================
public:
	//기본 이동 함수 : 앞뒤 이동
	UFUNCTION()
		virtual void MoveForward(float Value);

	//기본 이동 함수 : 양옆 이동
	UFUNCTION()
		virtual void MoveRight(float Value);

	//기본 회전 함수 : 45도 만큼 카메라 전환
	UFUNCTION()
		virtual void SnapTurn(float Value);

	//SnapTurn이 연속으로 입력되는 것을 방지하는 함수
	UFUNCTION()
		void ResetSnapTurnControllerInput();

	//Jump를 활성화/비활성화 함
	UFUNCTION()
		void SetCanJump(bool NewState);

///============================================
/// Level Sequence / Level Streaming 관련 함수
///============================================
public:	
	UFUNCTION(Client, Reliable)
		void PlayLevelInitSequence();

	//크로스 페이드를 실제로 출력하는 로직, 각 자식 게임모드 클래스에서 바인딩 해야함
	//PlayerID 미사용 파라미터 제거 예정
	UFUNCTION(BlueprintCallable)
		float PlayLevelSequence(EPlayerLevelSequenceType TargetSequenceType);

	UFUNCTION()
		virtual void InitLevelSequence();

	//게임모드 레퍼런스 초기화
	UFUNCTION()
		void InitGameModeRef();

	//레벨 스크립트 레퍼런스를 초기화
	UFUNCTION()
		void InitLevelScriptRef();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		class APersistentLevelBase* GetLevelScriptRef() { return LevelScriptRef; }

	//현재 아이피 주소를 반환
	UFUNCTION(BlueprintCallable)
		FString GetCurrentIpAddress();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

///============================================
/// 컴포넌트  멤버
///============================================
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

///============================================
/// 비컴포넌트 멤버
///============================================
public:
	//레벨 시퀀스 배열 (0 : CrossFade, 1 : FadeIn, 2 : FadeOut)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		TArray<class ULevelSequence*> LevelSequenceList;

	//레벨 시퀀스 길이 배열 (MUST BE ADDED)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		TArray<float> LevelSequenceLengthList; 

	//C++ 딜레이 사용 위한 타이머 핸들 
	UPROPERTY()
		struct FTimerHandle WaitHandle;

	//점프가 가능한지? (BP에서 옵션 지정, 기본값 : t)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
		bool bCanJump = true; 

///============================================
/// private 멤버
///============================================
private:
	//SnapTurn 실행이 끝났는지? (연속 입력 방지)
	UPROPERTY()
		bool bSnapTurnIsFinished;

	UPROPERTY()
		int32 PlayerControllerID;

	//시퀀스 플레이어 (FadeIn & Out)
	UPROPERTY()
		TArray<class ULevelSequencePlayer*> LevelSequencePlayerList;

	UPROPERTY()
		class ADreamBoxGameModeBase* GamemodeRef;

	UPROPERTY()
		class APersistentLevelBase* LevelScriptRef;

};
