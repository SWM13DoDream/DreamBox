// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/MissionTrigger.h"
#include "../public/FirefighterGamemode.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMissionTrigger::AMissionTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOI_SCENE"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	MissionUpdateTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("MISSION_TRIGGER"));
	MissionUpdateTrigger->SetupAttachment(DefaultSceneRoot);
	MissionUpdateTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	MissionUpdateTrigger->SetWorldScale3D(FVector(3.0f, 0.5f, 5.0f));

	PrevMissionCheckTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("PREV_MISSION_CHECK_TRIGGER"));
	PrevMissionCheckTrigger->SetupAttachment(DefaultSceneRoot);
	PrevMissionCheckTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	PrevMissionCheckTrigger->SetWorldScale3D(FVector(3.0f, 1.125f, 1.0f));
}

// Called when the game starts or when spawned
void AMissionTrigger::BeginPlay()
{
	Super::BeginPlay();

	//트리거 볼륨 이벤트 바인딩
	MissionUpdateTrigger->OnComponentEndOverlap.AddDynamic(this, &AMissionTrigger::MissionUpdateEndOverlap);
	PrevMissionCheckTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMissionTrigger::PrevMissionCheckBeginOverlap);

	//이전 미션 필요 여부에 따라 콜리전 채널을 변경
	if (bIsRequirePrevMission) MissionUpdateTrigger->SetCollisionProfileName(FName("BlockAll"));
	else MissionUpdateTrigger->SetCollisionProfileName(FName("OverlapAll"));

	if (GetWorld()) //게임모드 레퍼런스 초기화 및 Delegate 이벤트 바인딩
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
		GamemodeRef->UpdateMissionList.AddDynamic(this, &AMissionTrigger::UpdateMissionTriggerCollision);
	}
}

// Called every frame
void AMissionTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissionTrigger::MissionUpdateEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !IsValid(GamemodeRef) || MissionID <= 0) return; //유효성 검사 
	UpdateMissionDelegate(); //미션 업데이트 델리게이트 호출
	Destroy(); //이후 액터 소멸
}

void AMissionTrigger::PrevMissionCheckBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//유효성 검사와 현재 MissionUpdateVolume이 Blocking(비활성화) 상태인지 체크
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player")) return;
	if (!IsValid(GamemodeRef) || MissionUpdateTrigger->GetCollisionProfileName() != "BlockAll") return;

	GamemodeRef->ShowScriptWithID.Broadcast(0, 16); //선행 미션을 먼저 수행하라는 스크립트 출력
}

void AMissionTrigger::UpdateMissionDelegate()
{
	if (!IsValid(GamemodeRef)) return; //게임모드 레퍼런스의 유효성을 검사
	
	//해당 트리거가 미션을 생성하는 볼륨인지 여부에 따라 Delegate 호출
	//아니라면? : 할당된 미션 ID를 기반으로 미션을 추가
	//맞다면? : 할당된 미션 ID를 기반으로 강제로 미션을 완료 시킴)
	if (!bIsMissionGoalVolume) GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, 0);
	else GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, 2e9);
}

void AMissionTrigger::UpdateMissionTriggerCollision(int32 PlayerId, int32 RemoveMissionId, int32 NewCondition)
{	
	//유효하지 않은 업데이트인지 확인
	if (NewCondition <= 0 || !bIsRequirePrevMission) return;
	//사라지는 미션이 지정한 미션의 ID와 같지 않다면 반환
	if (RemoveMissionId != PrevMissionID) return;
	MissionUpdateTrigger->SetCollisionProfileName(FName("OverlapAll"));
}
