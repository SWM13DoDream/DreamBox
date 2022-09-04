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

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("MISSION_TRIGGER"));
	TriggerVolume->SetRelativeLocation(FVector(0.0f));
	TriggerVolume->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AMissionTrigger::BeginPlay()
{
	Super::BeginPlay();

	//트리거 볼륨 이벤트 바인딩
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AMissionTrigger::OnComponentEndOverlap);

	//이전 미션 필요 여부에 따라 콜리전 채널을 변경
	if (bIsRequirePrevMission) TriggerVolume->SetCollisionProfileName(FName("BlockAll"));
	else TriggerVolume->SetCollisionProfileName(FName("OverlapAll"));

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

void AMissionTrigger::OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !IsValid(GamemodeRef) || MissionID <= 0) return; //유효성 검사 
	UpdateMissionDelegate(); //미션 업데이트 델리게이트 호출
	Destroy(); //이후 액터 소멸
}

void AMissionTrigger::UpdateMissionDelegate()
{
	if (!IsValid(GamemodeRef)) return; //게임모드 레퍼런스의 유효성을 검사
	
	//해당 트리거가 미션을 바로 제거하는 볼륨인지 여부에 따라 Delegate 호출
	//아니라면? : 할당된 미션 ID를 기반으로 미션을 추가
	//맞다면? : 할당된 미션 ID를 기반으로 강제로 미션을 완료 시킴)
	if (!bIsRemoveVolume) GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, 0);
	else GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, 2e9);
}

void AMissionTrigger::UpdateMissionTriggerCollision(int32 PlayerId, int32 RemoveMissionId, int32 NewCondition)
{	
	//유효하지 않은 업데이트인지 확인
	if (NewCondition <= 0 || !bIsRequirePrevMission) return;
	//사라지는 미션이 지정한 미션의 ID와 같지 않다면 반환
	if (RemoveMissionId != PrevMissionID) return;
	TriggerVolume->SetCollisionProfileName(FName("OverlapAll"));
}
