// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/VRCharacter.h"
#include "AstronautCharacter.generated.h"

/*
 - Name			: AAstronautCharacter
 - Author		: DEVroar
 - Descirption	: 우주비행사 Default Pawn (플레이어 캐릭터)
 - Date			: 2022/07/26
*/

UCLASS()
class DREAMBOX_API AAstronautCharacter : public AVRCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAstronautCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	// 인터렉션 키 Press에 바인딩
	UFUNCTION()
		void OnInteract();

	// 인터렉션 키 Release에 바인딩
	UFUNCTION()
		void ReleaseInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 캐릭터 무브먼트 컴포넌트 (BeginPlay에서 초기화)
	UCharacterMovementComponent* Movement;

	// 플레이어가 선택한 임무
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SelectedMission;

	// 플레이어의 이동 방식 (CSM 임무에서 사용)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MoveType;

// LEM 임무 전용 액터 컴포넌트 (CSM 임무 중에는 not available)  
public:
	// 캐릭터 VR Origin에 부착되는 타이머 표시 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* TimerWidget;

	// 캐릭터 VR Origin에 부착되는 미션 표시 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionWidget;

// CSM 선내 작업의 이동을 담당하는 메서드 및 필드
public:
	// Grip 누를 시 BP_AstronautCharacterVR에서 호출
	UFUNCTION(BlueprintCallable)
		void OnGrip(AActor* HandActor, bool bIsLeft);

	// Grip을 뗄 시 BP_AstronautCharacterVR에서 호출
	UFUNCTION(BlueprintCallable)
		void ReleaseGrip(AActor* HandActor, bool bIsLeft);

	// 선내 작업 Grip의 판정 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAGripRadius;

	// 선내 작업 OnGrip 시 힘이 작용하기 위한 최소 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPullingForceDistanceThreshold;

	// 선내 작업 OnGrip 시 이동 속도비
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPullingForceMultiplier;

	// 선내 작업 ReleaseGrip 시 이동 속도비
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPushingForceMultiplier;

private:
	// 왼손 및 오른손 홀딩 여부
	bool bIsGrabbingL, bIsGrabbingR;
	
	// 왼손 및 오른손 최근 홀딩 지점 (AstronautCharacter에 대한 손 오브젝트의 Relative Location으로 정의)
	FVector RecentGrabbingPointL, RecentGrabbingPointR;
};