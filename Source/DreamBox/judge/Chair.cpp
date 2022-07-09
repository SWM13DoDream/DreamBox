// Fill out your copyright notice in the Description page of Project Settings.


#include "./Chair.h"
#include "Components/WidgetComponent.h"

// Sets default values
AChair::AChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(80.0f, 80.0f, 60.0f));
	Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	
	RootComponent = Trigger;

}

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChair::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AChair::OnCharacterOverlap);
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChair::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AJudgeCharacter* JudgePlayer = Cast<AJudgeCharacter>(OtherActor))
	{
		JudgePlayer->GetCharacterMovement()->ToggleActive();
		JudgePlayer->WidgetInteraction->bEnableHitTesting = true;
	}
}

