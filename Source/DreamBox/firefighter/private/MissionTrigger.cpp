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
	
	//이벤트 바인딩
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AMissionTrigger::OnComponentEndOverlap);

	if (GetWorld()) //게임모드 레퍼런스 따옴
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
	UpdateMissionDelegate(); //델리게이트 호출 이후
	Destroy(); //액터 소멸
}

void AMissionTrigger::UpdateMissionDelegate()
{
	if (!IsValid(GamemodeRef)) return;
	GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, bIsRemoveTarget); //게임모드의 미션 업데이트 델리게이트 호출
}
