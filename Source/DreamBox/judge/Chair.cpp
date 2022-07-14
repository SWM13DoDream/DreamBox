// Fill out your copyright notice in the Description page of Project Settings.


#include "./Chair.h"
#include "./JudgeCharacter.h"
#include "./JudgeGameMode.h"

// Sets default values
AChair::AChair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = false;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = Body;
	Trigger->SetupAttachment(RootComponent);

	Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	Trigger->SetBoxExtent(FVector(80.0f, 80.0f, 60.0f));
	Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));


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
		
		AJudgeGameMode* GameMode = Cast<AJudgeGameMode>(GetWorld()->GetAuthGameMode());

	}
}

