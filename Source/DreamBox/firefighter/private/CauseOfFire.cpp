// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/CauseOfFire.h"
#include "../public/FirefighterCharacter.h"
#include "../public/FirefighterGamemode.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ACauseOfFire::ACauseOfFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetRelativeLocation(FVector(0.0f));
	SetRootComponent(DefaultSceneRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATIC_MESH"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);

	InteractionTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER_VOLUME"));
	InteractionTrigger->SetupAttachment(DefaultSceneRoot);
	InteractionTrigger->SetWorldScale3D(FVector(2.0f));

	GuideMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GUIDE_MESH"));
	GuideMesh->SetupAttachment(DefaultSceneRoot);
	GuideMesh->SetWorldScale3D(FVector(0.3f));

	EffectParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT_PARTICLE"));
	EffectParticle->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void ACauseOfFire::BeginPlay()
{
	Super::BeginPlay();
	
	GuideMesh->SetVisibility(false);
	EffectParticle->SetVisibility(false);

	InteractionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACauseOfFire::InteractionTriggerBeginOverlap);
	InteractionTrigger->OnComponentEndOverlap.AddDynamic(this, &ACauseOfFire::InteractionTriggerEndOverlap);

	if (GetWorld()) //Gamemode ���۷����� �ʱ�ȭ�ϰ�, �̼� ������Ʈ�� ���� �̺�Ʈ�� ���ε�
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
		GamemodeRef->UpdateMissionList.AddDynamic(this, &ACauseOfFire::TryActivateMissionActor);
	}
}

// Called every frame
void ACauseOfFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACauseOfFire::EndPlay(EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);
	//�Ҵ�� �̼��� ������Ʈ (�̼� �Ϸ� ���� ī��Ʈ�� 1����)
	GamemodeRef->UpdateMissionListComponent.Broadcast(0, MissionID, 1);
}

void ACauseOfFire::InteractionTriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !bIsActivated) return; //�÷��̾� ��ȿ�� �˻�� ���ͷ��� ���� ���� �˻�
	
	//�÷��̾ ������ �Ǹ�, ��ȣ�ۿ��� �����ϵ��� ��
	AFirefighterCharacter * PlayerCharacterRef = Cast<AFirefighterCharacter>(OtherActor);
	PlayerCharacterRef->SetCauseOfFireRef(this); //�� ������ �ּҸ� ����
	PlayerCharacterRef->SetInteractionType(EFirefighterInteractionType::E_INVESTIGATE);
	PlayerCharacterRef->SetIsReadyToInteraction(true);
}

void ACauseOfFire::InteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player")) return;

	//�÷��̾ ������ ���¿��� ����ٸ�, ��ȣ�ۿ��� �� �� ������ �ѹ�
	AFirefighterCharacter* PlayerCharacterRef = Cast<AFirefighterCharacter>(OtherActor);
	PlayerCharacterRef->SetCauseOfFireRef(nullptr); //�÷��̾ �����ϴ� �����͸� �ʱ�ȭ
	PlayerCharacterRef->SetInteractionType(EFirefighterInteractionType::E_NONE);
	PlayerCharacterRef->SetIsReadyToInteraction(false);
}

void ACauseOfFire::TryActivateMissionActor(int32 PlayerId, int32 NewMissionId, bool bIsRemove)
{
	//�߰��Ǵ� �̼��� �ƴϰų� ������ �̼� ID�� �ٸ��ٸ� ��ȯ
	if (bIsRemove || NewMissionId != MissionID) return; 
	
	bIsActivated = true; 
	GuideMesh->SetVisibility(true);
	EffectParticle->SetVisibility(true);
}

