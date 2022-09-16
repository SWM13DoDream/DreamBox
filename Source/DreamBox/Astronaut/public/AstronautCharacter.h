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

public:
	// 임무 시작
	UFUNCTION(BlueprintCallable)
		void InitializeMission();

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

public:
	// 특수 키 (Meta Quest 2 - R컨트롤러 A키) 입력 함수
	UFUNCTION(BlueprintCallable)
		void OnSpecialKey();

	UFUNCTION(BlueprintCallable)
		void ReleaseSpecialKey();

// LEM 임무 전용 액터 컴포넌트 (CSM 임무 중에는 not available)  
public:
	// 캐릭터 VR Origin에 부착되는 타이머 표시 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* TimerWidget;

	// 캐릭터 VR Origin에 부착되는 미션 표시 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionWidget;

// CSM 임무 전용 액터 컴포넌트 (LEM 임무 중에는 not available)
public:
	// 캐릭터에 부착되는 케이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCableComponent* Cable;

	// Hook을 연결할 오른손 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AActor* HookHand;

// CSM 임무 진행에 필요한 메서드
public:
	// 선외 작업 Hook에 사용할 오른손 액터를 등록. 파생 BP에서 구현
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void RegisterHookHand();

	// 정거장 선외로 이동
	UFUNCTION(BlueprintCallable)
		void StartEVA();

	// 정거장 선내로 이동
	UFUNCTION(BlueprintCallable)
		void ReturnIVA();

	// Grip 누를 시 BP_AstronautCharacterVR에서 호출
	UFUNCTION(BlueprintCallable)
		void OnGrip(AActor* HandActor, bool bIsLeft);

	// Grip을 뗄 시 BP_AstronautCharacterVR에서 호출
	UFUNCTION(BlueprintCallable)
		void ReleaseGrip(AActor* HandActor, bool bIsLeft);

	// 선외 작업 시 Hook을 연결
	UFUNCTION(BlueprintCallable)
		void ControlHook();

// CSM 선내 작업의 이동을 담당하는 퍼블릭 필드
public:
	// 선내 작업 Grip의 판정 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAGripRadius;

	// 선내 작업 OnGrip 시 이동 속도비
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPullingForceMultiplier;

	// 선내 작업 ReleaseGrip 시 이동 속도비
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPushingForceMultiplier;

// CSM 선외 작업의 기동을 담당하는 퍼블릭 필드
public:
	// 선외 작업 시 캐릭터 CapsuleComponent 높이 (콜리전 범위 변경)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVACharacterHeight;

	// 선외 작업 시 캐릭터 Pitch 시점 변경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVACharacterPitch;

	// 선외 작업 Grip의 판정 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVAGripRadius;

	// 선외 작업 OnGrip 시 이동 속도비
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVAPullingForceMultiplier;

	// 선외 작업 Grip을 모두 뗄 시 발생하는 외력 강도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVAExternalForceMagnitude;

	// 선외 작업에서 안전줄을 이용해 복귀하는 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVAHookForce;

	// 선외 작업 케이블 길이
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		float EVACableMaxLength;

private:
	// 왼손 및 오른손 홀딩 여부
	bool bIsGrabbingL, bIsGrabbingR;
	
	// 왼손 및 오른손 최근 홀딩 지점 (AstronautCharacter에 대한 손 오브젝트의 Relative Location으로 정의)
	FVector RecentGrabbingPointL, RecentGrabbingPointR;

	// 최근 고정 케이블 연결 지점
	FVector RecentHookPoint;

	// 선외 작업 시 1/120초마다 실행되어, 케이블의 길이가 너무 길어지면 외력을 제거 
	void EVACableChecker();
	FTimerHandle TimerHandler;

	// 케이블의 길이를 반환하는 함수. 편의를 위해 선언
	float GetCableLength();
};