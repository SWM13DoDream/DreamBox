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
}

// Called when the game starts or when spawned
void ARescueGoal::BeginPlay()
{
	Super::BeginPlay();
	
	EventTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARescueGoal::TriggerBeginOverlap); //오버랩 이벤트
	if (GetWorld()) GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode()); //게임모드 레퍼런스 초기화
}

// Called every frame
void ARescueGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ARescueGoal::TriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !IsValid(GamemodeRef)) return; //캐릭터와 게임모드 유효성 검사

	FirefighterCharacterRef = Cast<AFirefighterCharacter>(OtherActor); //레퍼런스 지정
	if (!FirefighterCharacterRef->GetIsCarrying()) return; //캐릭터를 불러올 수 없거나 업고 있는 캐릭터가 없다면 반환

	AInjuredCharacter* injuredCharacter = FirefighterCharacterRef->GetInjuredCharacterRef(); //레퍼런스 지정
	if (!IsValid(injuredCharacter)) return; //구조대상 캐릭터가 유효하지 않거나 미션ID가 다르다면 반환
	if (MissionID != 0 && MissionID != injuredCharacter->GetMissionID()) return; //ID가 0? : 범용

	GamemodeRef->PlayCrossFadeAnimation.Broadcast(0);  //CrossFade 호출
	GamemodeRef->UpdateMissionListComponent.Broadcast(0, injuredCharacter->GetMissionID(), 1); //미션 업데이트 
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&](){ 
		FirefighterCharacterRef->PutInjuredCharacter(); //CrossFade 도중에 캐릭터를 내려둠
		CurrentRescueCount += 1; //구조한 인원 수를 카운팅
		if(TargetRescueCount == CurrentRescueCount) Destroy(); //목표로 하고 있는 인원 수가 되었다면 Destroy
	}), 0.75f, false);
}