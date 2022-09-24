// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/VRCharacter.h"
#include "FirefighterInteractionType.h"
#include "FirefighterCharacter.generated.h"

/*
 - Name        : AFirefighterCharacter
 - Descirption : Firefighter 직업의 메인 Playable 캐릭터
 - Date        : 2022/09/24 LJH
*/

UCLASS()
class DREAMBOX_API AFirefighterCharacter : public AVRCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AFirefighterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	/*-------- Interaction -----------------*/
	//상호작용을 시도 : bIsReadyToInteraction과 InteractionType 기반으로 결정
	UFUNCTION()
		void TryInteraction();

	//상호작용 : 물을 발사
	UFUNCTION()
		void Fire();

	//상호작용 : 물 발사 중지
	UFUNCTION(BlueprintCallable)
		void StopFire();

	//상호작용 : 화재 원인 조사
	UFUNCTION(BlueprintCallable)
		void InvestigateCauseOfFire();

	//상호작용 : 다친 캐릭터를 어깨에 짊어짐
	UFUNCTION(BlueprintCallable)
		void CarryInjuredCharacter();

	//상호작용 : 업고 있는 캐릭터를 내려놓음
	UFUNCTION(BlueprintCallable)
		void PutInjuredCharacter();

public: // Set Get
	//상호작용 할 화재원인액터의 레퍼런스 지정
	UFUNCTION(BlueprintCallable)
		void SetCauseOfFireRef(ACauseOfFire* NewCauseOfFire) { CauseOfFireRef = NewCauseOfFire; }

	//업을 캐릭터의 레퍼런스를 지정
	UFUNCTION(BlueprintCallable)
		void SetInjuredCharacterRef(AInjuredCharacter* NewInjuredCharacter) { InjuredCharacterRef = NewInjuredCharacter; }

	//인터렉션 타입을 지정
	UFUNCTION(BlueprintCallable)
		void SetInteractionType(EFirefighterInteractionType NewType) { InteractionType = NewType; }

	//Interaction이 가능한지 여부를 업데이트
	UFUNCTION(BlueprintCallable)
		void SetIsReadyToInteraction(bool NewState) { bIsReadyToInteraction = NewState; }

	//플레이어가 InjurecCharacter 객체를 업고있는지 업데이트
	UFUNCTION()
		void SetIsCarrying(bool NewState) { bIsCarrying = NewState; }

	//Interaction 관련 멤버 초기화
	UFUNCTION()
		void ResetInteractionState(); 

	//Interaction이 가능한지 여부 반환
	UFUNCTION(BlueprintCallable)
		bool GetIsReadyToInteraction() const { return bIsReadyToInteraction; }

	//캐릭터가 어떤 것을 메고 있는지 반환
	UFUNCTION(BlueprintCallable)
		bool GetIsCarrying() const { return bIsCarrying;  }

	//업고있는 InjuredCharacter의 레퍼런스를 반환
	UFUNCTION(BlueprintCallable)
		AInjuredCharacter* GetInjuredCharacterRef() const { return InjuredCharacterRef;  }

	//캐릭터의 Visibility를 설정
	UFUNCTION()
		void SetCharacterVisibility(bool NewState) const;

public: //Delegate 관련, 플레이어를 거치는 이유? - 멀티플레이 및 관전 기능 감안
	UFUNCTION()
		void UpdateMissionList(int32 PlayerID, int32 MissionID, int32 Variable);

	UFUNCTION()
		void ShowScriptWithID(int32 PlayerID, int32 ScriptID);

	UFUNCTION()
		void ShowScriptWithString(int32 PlayerID, FString Script);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//캐릭터가 소유한 소방 호스 관창
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* FireHose; 

	//구조되고있는 캐릭터가 부착될 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* RescueSocket;

	//캐릭터의 손전등 불빛 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpotLightComponent* FlashLight;

	UPROPERTY(EditAnywhere)
		UChildActorComponent* ScriptManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UChildActorComponent* MissionManager;

private:
	//게임모드 레퍼런스
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef;

	//업을 캐릭터의 레퍼런스 (InValid 할 경우 불가능)
	UPROPERTY()
		class AInjuredCharacter* InjuredCharacterRef;

	//화재 원인 액터 레퍼런스 
	UPROPERTY()
		class ACauseOfFire* CauseOfFireRef;

	//MissionManager 레퍼런스
	UPROPERTY()
		class AMissionManager* MissionManagerRef;

	//ScriptManager 레퍼런스
	UPROPERTY()
		class AScriptManager* ScriptManagerRef;

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