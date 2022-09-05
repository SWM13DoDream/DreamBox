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

	//Ʈ���� ���� �̺�Ʈ ���ε�
	MissionUpdateTrigger->OnComponentEndOverlap.AddDynamic(this, &AMissionTrigger::MissionUpdateEndOverlap);
	PrevMissionCheckTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMissionTrigger::PrevMissionCheckBeginOverlap);

	//���� �̼� �ʿ� ���ο� ���� �ݸ��� ä���� ����
	if (bIsRequirePrevMission) MissionUpdateTrigger->SetCollisionProfileName(FName("BlockAll"));
	else MissionUpdateTrigger->SetCollisionProfileName(FName("OverlapAll"));

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

void AMissionTrigger::MissionUpdateEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !IsValid(GamemodeRef) || MissionID <= 0) return; //��ȿ�� �˻� 
	UpdateMissionDelegate(); //�̼� ������Ʈ ��������Ʈ ȣ��
	Destroy(); //���� ���� �Ҹ�
}

void AMissionTrigger::PrevMissionCheckBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//��ȿ�� �˻�� ���� MissionUpdateVolume�� Blocking(��Ȱ��ȭ) �������� üũ
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player")) return;
	if (!IsValid(GamemodeRef) || MissionUpdateTrigger->GetCollisionProfileName() != "BlockAll") return;

	GamemodeRef->ShowScriptWithID.Broadcast(0, 16); //���� �̼��� ���� �����϶�� ��ũ��Ʈ ���
}

void AMissionTrigger::UpdateMissionDelegate()
{
	if (!IsValid(GamemodeRef)) return; //���Ӹ�� ���۷����� ��ȿ���� �˻�
	
	//�ش� Ʈ���Ű� �̼��� �����ϴ� �������� ���ο� ���� Delegate ȣ��
	//�ƴ϶��? : �Ҵ�� �̼� ID�� ������� �̼��� �߰�
	//�´ٸ�? : �Ҵ�� �̼� ID�� ������� ������ �̼��� �Ϸ� ��Ŵ)
	if (!bIsMissionGoalVolume) GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, 0);
	else GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, 2e9);
}

void AMissionTrigger::UpdateMissionTriggerCollision(int32 PlayerId, int32 RemoveMissionId, int32 NewCondition)
{	
	//��ȿ���� ���� ������Ʈ���� Ȯ��
	if (NewCondition <= 0 || !bIsRequirePrevMission) return;
	//������� �̼��� ������ �̼��� ID�� ���� �ʴٸ� ��ȯ
	if (RemoveMissionId != PrevMissionID) return;
	MissionUpdateTrigger->SetCollisionProfileName(FName("OverlapAll"));
}
