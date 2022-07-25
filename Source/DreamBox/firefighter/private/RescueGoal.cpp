// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/RescueGoal.h"
#include "../public/FirefighterCharacter.h"
#include "../public/InjuredCharacter.h"

// Sets default values
ARescueGoal::ARescueGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EventTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("EVENT_TRIGGER"));
	EventTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARescueGoal::BeginPlay()
{
	Super::BeginPlay();
	
	EventTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARescueGoal::TriggerBeginOverlap); //오버랩 이벤트

	if (GetWorld()) //게임모드 레퍼런스 따옴
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
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
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !IsValid(GamemodeRef)) return; //캐릭터와 게임모드 유효성 검사

	FirefighterCharacterRef = Cast<AFirefighterCharacter>(OtherActor); //레퍼런스 지정
	if (!FirefighterCharacterRef->GetIsCarrying()) return; //캐릭터를 불러올 수 없거나 업고 있는 캐릭터가 없다면 반환

	AInjuredCharacter* injuredCharacter = FirefighterCharacterRef->GetInjuredCharacterRef(); //레퍼런스 지정
	if (!IsValid(injuredCharacter)) return; //구조대상 캐릭터가 유효하지 않거나 미션ID가 다르다면 반환
	if (MissionID != 0 && MissionID != injuredCharacter->GetMissionID()) return; //ID가 0? : 범용

	GamemodeRef->PlayFadeInOutAnimation.Broadcast(0);  //FadeIn 애니메이션 
	GamemodeRef->UpdateMissionListComponent.Broadcast(0, injuredCharacter->GetMissionID(), 1); //미션 업데이트 
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&](){ //FadeIn 중간에 캐릭터를 내려둠
		FirefighterCharacterRef->PutInjuredCharacter();
		CurrentRescueCount += 1;
		if(TargetRescueCount == CurrentRescueCount) Destroy();
	}), 0.75f, false);
}