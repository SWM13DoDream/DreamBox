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

	// VR 캐릭터 이동 재정의
		void MoveForward(float Value) override;

	// VR 캐릭터 이동 재정의
		void MoveRight(float Value) override;

	// 인터렉션 키 Press에 바인딩
	UFUNCTION()
		void OnInteract();

	// 인터렉션 키 Release에 바인딩
	UFUNCTION()
		void ReleaseInteract();

protected:
	// 실제 우주비행사 컨텐츠 시작은 아래 멀티플레이 관련 함수에서 Client RPC로 정의되어 있음.
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

	// 미션로직-뷰포트 중계 액터 컨트롤러
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
		class AGamemodeArbiter* Arbiter;

public:
	// 특수 키 (Meta Quest 2 - R컨트롤러 A키) 입력 함수
	UFUNCTION(BlueprintCallable)
		void OnSpecialKey();

	UFUNCTION(BlueprintCallable)
		void ReleaseSpecialKey();

/* 임무 로직 진행 관련 메서드. 위젯&시퀀서를 사용하는 경우에는 파생 BP로 구현 */
public:
	// 중계자 등록. BeginPlay와 동시에 레벨 내 GamemodeArbiter로부터 호출
	UFUNCTION(BlueprintCallable)
		void RegisterArbiter(class AGamemodeArbiter* Invoker);

	// 시작 시퀀서 재생. 게임 모드 PostLogin 시점에 RPC로 호출된 함수에서 함께 호출됨
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "PreMission")
		void PlayInitialSequence();

	// 플레이어 대기 중일 때 다른 플레이어 접속 시 대기 해제
	UFUNCTION(BlueprintCallable)
		void CloseWaitingPanel();

	// 미션 선택 위젯 패널 열기 (Arbiter 사용)
	UFUNCTION(BlueprintCallable)
		void OpenSelectMissionPanel();

	// 미션 선택 시 외부 위젯으로부터 호출
	UFUNCTION(BlueprintCallable)
		void SelectMission(int32 Mission);

	// 미션 선택 창 -> 미션 시작 위치로 자연스러운 이동을 위해 시퀀서 동작
	UFUNCTION(BlueprintImplementableEvent, Category = "PreMission")
		void PlayMissionInitSequence();

	// 임무 시작. PlayMissionInitSequence에 의해 호출
	UFUNCTION(BlueprintCallable)
		void InitializeMission();

	// 정보 위젯 열기. FName 파라미터에 따라 다른 로직을 사용함
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void OpenInfoWidget(const FName& Key);

	// 정보 위젯 닫기. 역시 FName 파라미터에 따라 다른 로직을 사용함
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void CloseInfoWidget(const FName& Key);

	// 특수 기능 함수: 시퀀서를 호출하여 화면 크로스페이드
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void PlayCrossFade();

/* 임무 공통 액터 컴포넌트 */
public:
	// 캐릭터 카메라에 부착되는 중요 안내 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* InfoWidget;

	// 캐릭터 카메라에 부착되는 다이얼로그 컨트롤러 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* DialogController;

/* 임무 진행 관련 제어 변수 (미션 관련 변수는 대부분 LEM에서만 사용) */
public:
	// bool 타입으로 메인 미션 관리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsMissionDone;

	// TArray<bool> 타입으로 서브 미션 관리 (Expected Length = 6)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<bool> bIsSubmissionDone;

	// TArray<int> 타입으로 랜덤으로 선택된 서브 미션 관리 (Expected Length = 3)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> RandomSubmissionIndices;

	// Text 타입의 메인 미션 위젯 표시값
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText MainMissionText;

	// TArray<FText> 타입의 서브 미션 위젯 표시값 (Max Length = 3)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FText> SubMissionText;

	// 플레이어가 움직이거나 기타 행동을 할 수 있는지 여부를 관리.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bMovable;

	// 타이머에 표시되는 시간을 관리. TIME_PERIOD가 사령선이 도착하는 한 주기를 나타냄 (현재 설정: 5분)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Time;

/* LEM 임무 전용 액터 컴포넌트(CSM 임무 중에는 not available) */
public:
	// 캐릭터 VR Origin에 부착되는 타이머 표시 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* TimerWidget;

	// 캐릭터 VR Origin에 부착되는 미션 표시 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionWidget;

private:
	// 타이머 위젯 컨트롤러 (탐사선 임무 InitializeMissions에서 초기화)
	class UTimerWidget* TimerController;

	// 미션 위젯 컨트롤러 (탐사선 임무 InitializeMissions에서 초기화)
	class UMissionWidget* MissionController;

	// 1초마다 실행되는 타이머 핸들러
	void MissionTick();
	FTimerHandle MissionTickHandler;

/* LEM 임무 전용 미션 진행 메서드 */
public:
	// 탐사선 메인 임무 완료
	UFUNCTION(BlueprintCallable)
		void DoMainMission();

	// 탐사선 서브 임무 완료
	UFUNCTION(BlueprintCallable)
		void DoSubMission(int32 Index);

	// 탐사선 외내부 이동에 따른 캐릭터 위치 변경
	UFUNCTION(BlueprintCallable)
		void MoveLEM(bool bIsEntering);

	// 탐사선 임무가 종료될 수 있는지 체크 (Time으로 체크)
	UFUNCTION(BlueprintCallable)
		bool IsAboardable();

/* CSM 임무 전용 액터 컴포넌트 (LEM 임무 중에는 not available) */
public:
	// 캐릭터에 부착되는 케이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCableComponent* Cable;

	// Hook을 연결할 오른손 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AActor* HookHand;

/* CSM 임무 진행에 필요한 메서드 */
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

/* CSM 선내 작업의 이동을 담당하는 퍼블릭 필드 */
public:
	// 선내 작업 Grip의 판정 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAGripRadius;

	// 선내 작업 OnGrip 시 이동 속도비
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPullingForceMultiplier;

	// 선내 작업 OnGrip 시 속도 감소 기간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		int32 IVAPullingForceDecrementInterval;

	// 선내 작업 ReleaseGrip 시 이동 속도비
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IVA")
		float IVAPushingForceMultiplier;

/* CSM 선외 작업의 기동을 담당하는 퍼블릭 필드 */
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

	// 선외 작업 OnGrip 시 속도 감소 기간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EVA")
		int32 EVAPullingForceDecrementInterval;

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

	// 최근 pulling force 정보 (점진적 속도 감소에 필요)
	FVector RecentPullingForce;

	// Pulling Force 감소 카운터
	int32 PullingForceDecrementCounter;

	// 최근 고정 케이블 연결 지점
	FVector RecentHookPoint;

	// 사령선 임무 시 1/120초마다 실행되어, 캐릭터에게 적용하는 물리 정보를 체크
	void ForceChecker();
	FTimerHandle ForceCheckHandler;

	// 케이블의 길이를 반환하는 함수. 편의를 위해 선언
	float GetCableLength();

// ======================================= //
// 여기부터는 서버 관련 프로퍼티와 함수입니다. //
// ======================================= //

public:
	// 컨텐츠 시작 함수. 게임 모드로부터 호출
	UFUNCTION(Client, Reliable)
		void OnRPCStartContent();

	// 미션을 선택하여 게임 모드에 등록, 다른 클라이언트에 대해 OnRPCCheckReadyState 호출
	// 만약 다른 클라이언트가 아직 선택하지 않은 상태면 미션 Lock 처리
	// 다른 클라이언트도 미션을 선택한 상태면 해당 클라이언트에서도 미션 시작
	UFUNCTION(Server, Reliable)
		void MakeRPCSelectMission(int32 Mission);

	// 위 MakeRPCSelectMission으로부터 호출. 게임 모드에 접근할 수 없음에 주의
	UFUNCTION(Client, Reliable)
		void OnRPCCheckReadyState(bool bStartMission, int32 MissionToLock);

private:
	bool bIsWaitingPlayer;
};