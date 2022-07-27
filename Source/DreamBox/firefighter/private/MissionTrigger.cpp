// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/MissionTrigger.h"

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
	
	//�̺�Ʈ ���ε�
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AMissionTrigger::OnComponentEndOverlap);

	if (GetWorld()) //���Ӹ�� ���۷��� ����
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
	}
}

// Called every frame
void AMissionTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissionTrigger::OnComponentEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !IsValid(GamemodeRef)) return;
	UpdateMissionDelegate(); //��������Ʈ ȣ�� ����
	Destroy(); //���� �Ҹ�
}

void AMissionTrigger::UpdateMissionDelegate()
{
	if (!IsValid(GamemodeRef)) return;
	GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, bIsRemoveTarget); //���Ӹ���� �̼� ������Ʈ ��������Ʈ ȣ��
}
