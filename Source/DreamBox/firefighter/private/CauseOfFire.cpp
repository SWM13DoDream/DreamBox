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

	if (GetWorld()) //Gamemode 레퍼런스를 초기화하고, 미션 업데이트를 위해 이벤트를 바인딩
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
	//할당된 미션을 업데이트 (미션 완료 조건 카운트를 1증가)
	GamemodeRef->UpdateMissionListComponent.Broadcast(0, MissionID, 1);
}

void ACauseOfFire::InteractionTriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !bIsActivated) return; //플레이어 유효성 검사와 인터렉션 가능 조건 검사
	
	//플레이어가 오버랩 되면, 상호작용이 가능하도록 함
	AFirefighterCharacter * PlayerCharacterRef = Cast<AFirefighterCharacter>(OtherActor);
	PlayerCharacterRef->SetCauseOfFireRef(this); //이 액터의 주소를 전달
	PlayerCharacterRef->SetInteractionType(EFirefighterInteractionType::E_INVESTIGATE);
	PlayerCharacterRef->SetIsReadyToInteraction(true);
}

void ACauseOfFire::InteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player")) return;

	//플레이어가 오버랩 상태에서 벗어난다면, 상호작용을 할 수 없도록 롤백
	AFirefighterCharacter* PlayerCharacterRef = Cast<AFirefighterCharacter>(OtherActor);
	PlayerCharacterRef->SetCauseOfFireRef(nullptr); //플레이어가 참조하던 포인터를 초기화
	PlayerCharacterRef->SetInteractionType(EFirefighterInteractionType::E_NONE);
	PlayerCharacterRef->SetIsReadyToInteraction(false);
}

void ACauseOfFire::TryActivateMissionActor(int32 PlayerId, int32 NewMissionId, bool bIsRemove)
{
	//추가되는 미션이 아니거나 지정한 미션 ID와 다르다면 반환
	if (bIsRemove || NewMissionId != MissionID) return; 
	
	bIsActivated = true; 
	GuideMesh->SetVisibility(true);
	EffectParticle->SetVisibility(true);
}

