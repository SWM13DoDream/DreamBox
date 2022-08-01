// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/MissionTrigger.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMissionTrigger::AMissionTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOI_SCENE"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("MISSION_TRIGGER"));
	//TriggerVolume->SetWorldScale3D({ 4.0f, 0.5f, 2.0f });
	TriggerVolume->SetRelativeLocation(FVector(0.0f));
	TriggerVolume->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AMissionTrigger::BeginPlay()
{
	Super::BeginPlay();

	//Init Trigger Volume
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AMissionTrigger::OnComponentEndOverlap);

	if (bIsRequirePrevMission)
	{
		TriggerVolume->SetCollisionProfileName(FName("BlockAll"));
	}
	else
	{
		TriggerVolume->SetCollisionProfileName(FName("OverlapAll"));
	}


	if (GetWorld()) //���Ӹ�� ���۷��� ����
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
		GamemodeRef->UpdateMissionListComponent.AddDynamic(this, &AMissionTrigger::UpdateMissionTriggerCollision);
	}
}

// Called every frame
void AMissionTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissionTrigger::OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !IsValid(GamemodeRef) || MissionID <= 0) return;
	UpdateMissionDelegate(); //��������Ʈ ȣ�� ����
	Destroy(); //���� �Ҹ�
}

void AMissionTrigger::UpdateMissionDelegate()
{
	if (!IsValid(GamemodeRef)) return;
	if (!bIsRemoveVolume)
	{
		GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, bIsRemoveVolume); //���Ӹ���� �̼� ������Ʈ ��������Ʈ ȣ��
	}
	else
	{
		GamemodeRef->UpdateMissionListComponent.Broadcast(0, MissionID, bIsRemoveVolume);
	}
}

void AMissionTrigger::UpdateMissionTriggerCollision(int32 PlayerId, int32 RemoveMissionId, int32 NewCondition)
{	
	//Ư�� �̼��� �����ϴ� �����̰ų� Ÿ���� �ٸ��ٰų�,
	if (NewCondition <= 0 || !bIsRequirePrevMission) return;
	if (RemoveMissionId != PrevMissionID) return;
	TriggerVolume->SetCollisionProfileName(FName("OverlapAll"));
}
