// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Character.h"
#include "InjuredCharacter.h"
#include "TimerManager.h"
#include "CauseOfFire.h"
#include "FirefighterGamemode.h"
#include "FirefighterInteractionType.h"
#include "FirefighterCharacter.generated.h"

/*
 - Name        : AFirefighterCharacter
 - Descirption : Firefighter 직업의 메인 Playable 캐릭터
 - Date        : 2022/07/20 LJH
*/

UCLASS()
class DREAMBOX_API AFirefighterCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AFirefighterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//기본 이동 함수 : 앞뒤 이동
	UFUNCTION()
		void MoveForward(float Value);

	//기본 이동 함수 : 양옆 이동
	UFUNCTION()
		void MoveRight(float Value);

	/*-------- Interaction -----------------*/
	//상호작용을 시도 : bIsReadyToInteraction과 InteractionType 기반으로 결정
	UFUNCTION()
		void TryInteraction();

	//물을 발사
	UFUNCTION()
		void Fire();

	//물 발사 중지
	UFUNCTION(BlueprintCallable)
		void StopFire();

	UFUNCTION(BlueprintCallable)
		void InvestigateCauseOfFire();

	//Interaction) 다친 캐릭터를 어깨에 짊어짐
	UFUNCTION(BlueprintCallable)
		void CarryInjuredCharacter();

	//Interaction) 업고 있는 캐릭터를 내려놓음
	UFUNCTION(BlueprintCallable)
		void PutInjuredCharacter();

	//인터렉션 할 화재원인액터의 레퍼런스 지정
	UFUNCTION(BlueprintCallable)
		void SetCauseOfFireRef(ACauseOfFire* NewCauseOfFire);

	//업을 캐릭터의 레퍼런스를 지정
	UFUNCTION(BlueprintCallable)
		void SetInjuredCharacterRef(AInjuredCharacter* NewInjuredCharacter);

	//인터렉션 타입을 지정
	UFUNCTION(BlueprintCallable)
		void SetInteractionType(EFirefighterInteractionType NewType);

	//Interaction이 가능한지 여부를 업데이트
	UFUNCTION(BlueprintCallable)
		void SetIsReadyToInteraction(bool NewState);

	//플레이어가 InjurecCharacter 객체를 업고있는지 업데이트
	UFUNCTION()
		void SetIsCarrying(bool NewState);

	//Interaction 관련 멤버 초기화
	UFUNCTION()
		void ResetInteractionState(); 

	//Interaction이 가능한지 여부 반환
	UFUNCTION(BlueprintCallable)
		bool GetIsReadyToInteraction() const { return bIsReadyToInteraction; }

	//캐릭터가 어떤 것을 메고 있는지 반환
	UFUNCTION(BlueprintCallable)
		bool GetIsCarrying() const { return bIsCarrying;  }

	UFUNCTION(BlueprintCallable)
		AInjuredCharacter* GetInjuredCharacterRef() const { return InjuredCharacterRef;  }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//VR Immersive 에셋 사용을 위한 임시 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* VROrigin;

	//VR Immersive 에셋 사용을 위한 임시 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* SpectatorRef;

	//소방호스 액터 : AFireHose 클래스를 지정.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* FireHose;

	//캐릭터의 메인 카메라 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* FollowingCamera;

	//구조되고있는 캐릭터가 부착될 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* RescueSocket;

	//캐릭터의 손전등 불빛 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpotLightComponent* FlashLight;

private:
	//게임모드 레퍼런스
	UPROPERTY()
		AFirefighterGamemode* GamemodeRef;

	//업을 캐릭터의 레퍼런스 (InValid 할 경우 불가능)
	UPROPERTY()
		AInjuredCharacter* InjuredCharacterRef;

	//화재 원인 액터 레퍼런스 
	UPROPERTY()
		ACauseOfFire* CauseOfFireRef;

	//C++ 딜레이 사용 위한 타이머 핸들 : 미사용
	UPROPERTY()
		FTimerHandle WaitHandle;

	//현재 가능한 InteractionType
	UPROPERTY()
		EFirefighterInteractionType InteractionType;

	//현재 업고 있는지?
	UPROPERTY()
		bool bIsCarrying;

	//상호작용이 가능한가?
	UPROPERTY()
		bool bIsReadyToInteraction;
};