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

	//Ʈ���� ���� �̺�Ʈ ���ε�
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AMissionTrigger::OnComponentEndOverlap);

	//���� �̼� �ʿ� ���ο� ���� �ݸ��� ä���� ����
	if (bIsRequirePrevMission) TriggerVolume->SetCollisionProfileName(FName("BlockAll"));
	else TriggerVolume->SetCollisionProfileName(FName("OverlapAll"));

	if (GetWorld()) //���Ӹ�� ���۷��� �ʱ�ȭ �� Delegate �̺�Ʈ ���ε�
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
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !IsValid(GamemodeRef) || MissionID <= 0) return; //��ȿ�� �˻� 
	UpdateMissionDelegate(); //�̼� ������Ʈ ��������Ʈ ȣ��
	Destroy(); //���� ���� �Ҹ�
}

void AMissionTrigger::UpdateMissionDelegate()
{
	if (!IsValid(GamemodeRef)) return; //���Ӹ�� ���۷����� ��ȿ���� �˻�
	
	//�ش� Ʈ���Ű� �̼��� �ٷ� �����ϴ� �������� ���ο� ���� Delegate ȣ��
	//�ƴ϶��? : �Ҵ�� �̼� ID�� ������� �̼��� �߰�
	//�´ٸ�? : �Ҵ�� �̼� ID�� ������� ������ �̼��� �Ϸ� ��Ŵ)
	if (!bIsRemoveVolume) GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, 0);
	else GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, 2e9);
}

void AMissionTrigger::UpdateMissionTriggerCollision(int32 PlayerId, int32 RemoveMissionId, int32 NewCondition)
{	
	//��ȿ���� ���� ������Ʈ���� Ȯ��
	if (NewCondition <= 0 || !bIsRequirePrevMission) return;
	//������� �̼��� ������ �̼��� ID�� ���� �ʴٸ� ��ȯ
	if (RemoveMissionId != PrevMissionID) return;
	TriggerVolume->SetCollisionProfileName(FName("OverlapAll"));
}
