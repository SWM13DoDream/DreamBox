// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/StairPortal.h"
#include "../public/FirefighterGamemode.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AStairPortal::AStairPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT_COMPONENT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER_VOLUME"));
	TriggerVolume->SetupAttachment(DefaultSceneRoot);
	TriggerVolume->SetRelativeScale3D(FVector(0.07f, 2.5f, 1.5f));
}

// Called when the game starts or when spawned
void AStairPortal::BeginPlay()
{
	Super::BeginPlay();
	
	//트리거 볼륨 이벤트 바인딩
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AStairPortal::OnComponentBeginOverlap);

	if (GetWorld()) //게임모드 레퍼런스 초기화 및 Delegate 이벤트 바인딩
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
		GamemodeRef->UpdateMissionList.AddDynamic(this, &AStairPortal::ActivatePortal);
	}
}

// Called every frame
void AStairPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStairPortal::ActivatePortal(int32 PlayerID, int32 MissionID, int32 Variable)
{
	if (Variable != 0) return;
	if (MissionID == TargetMissionID && bIsFirstFloor)
	{
		MissionDestination = 1;
	}
	else
	{
		MissionDestination = -1;
	}
}

void AStairPortal::OnComponentBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player")) return;

	GamemodeRef->CrossFadeAnimationEvent.Broadcast(0);

	PlayerCharacterRef = Cast<ACharacter>(OtherActor);
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
		int32 TargetIdx = MissionDestination == -1 ? DefaultDestination : MissionDestination;
		if (TargetIdx >= TeleportPointArray.Num()) return;
		FVector TargetLocation = TeleportPointArray[TargetIdx]->GetActorLocation();
		PlayerCharacterRef->SetActorLocation(TargetLocation + FVector(0.0f, 100.0f, 0.0f));

		FRotator TargetRotation = UKismetMathLibrary::NormalizedDeltaRotator(GetActorRotation(), PlayerCharacterRef->GetActorRotation());
		PlayerCharacterRef->AddActorWorldRotation(TargetRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}), 0.75f, false);
}
