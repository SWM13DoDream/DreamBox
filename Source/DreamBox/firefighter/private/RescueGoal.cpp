// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/RescueGoal.h"
#include "../public/FirefighterCharacter.h"
#include "../public/FirefighterGamemode.h"
#include "../public/InjuredCharacter.h"
#include "TimerManager.h"

// Sets default values
ARescueGoal::ARescueGoal() 
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	EventTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("EVENT_TRIGGER"));
	EventTrigger->SetupAttachment(DefaultSceneRoot);
	
	DestinationGuideMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DESTINATION_GUIDE"));
	DestinationGuideMesh->SetupAttachment(DefaultSceneRoot);
	DestinationGuideMesh->SetVisibility(false);

	DestinationArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DESTINATION_ARROW"));
	DestinationArrowMesh->SetupAttachment(DefaultSceneRoot);
	DestinationArrowMesh->SetVisibility(false);
 }

// Called when the game starts or when spawned
void ARescueGoal::BeginPlay()
{
	Super::BeginPlay();
	
	EventTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARescueGoal::TriggerBeginOverlap); //������ �̺�Ʈ
	if (GetWorld())
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode()); //���Ӹ�� ���۷��� �ʱ�ȭ
		GamemodeRef->UpdateMissionList.AddDynamic(this, &ARescueGoal::TryActivateActor);
	}
}

// Called every frame
void ARescueGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ARescueGoal::TriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !IsValid(GamemodeRef) || !bIsActivated) return; //ĳ���Ϳ� ���Ӹ�� ��ȿ�� �˻�

	FirefighterCharacterRef = Cast<AFirefighterCharacter>(OtherActor); //���۷��� ����
	if (!FirefighterCharacterRef->GetIsCarrying()) return; //ĳ���͸� �ҷ��� �� ���ų� ���� �ִ� ĳ���Ͱ� ���ٸ� ��ȯ

	AInjuredCharacter* injuredCharacter = FirefighterCharacterRef->GetInjuredCharacterRef(); //���۷��� ����
	if (!IsValid(injuredCharacter)) return; //������� ĳ���Ͱ� ��ȿ���� �ʰų� �̼�ID�� �ٸ��ٸ� ��ȯ

	if (IsValid(FirefighterCharacterRef))
	{
		FirefighterCharacterRef->PlayCrossFadeAnim();
	}

	if (IsValid(GamemodeRef))
	{
		GamemodeRef->UpdateMissionList.Broadcast(0, injuredCharacter->GetMissionID(), 1); //�̼� ������Ʈ
	}

	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&](){ 
		FirefighterCharacterRef->PutInjuredCharacter(); //CrossFade ���߿� ĳ���͸� ������
		CurrentRescueCount += 1; //������ �ο� ���� ī����
		if(TargetRescueCount == CurrentRescueCount) Destroy(); //��ǥ�� �ϰ� �ִ� �ο� ���� �Ǿ��ٸ� Destroy
	}), 0.75f, false);
}

void ARescueGoal::TryActivateActor(int32 PlayerId, int32 MissionId, int32 Variable)
{
	//������Ʈ �Ǵ� �̼��� ����
	if (Variable != 0) return;
		
	bool bIsContain = false;
	for (const int32& RescueMissionID : RescueMissionIdList)
	{
		if (RescueMissionID != MissionId) continue;
		bIsContain = true;
		break;
	}
	bIsActivated = bIsContain;
	DestinationGuideMesh->SetVisibility(bIsContain);
	DestinationArrowMesh->SetVisibility(bIsContain);
}