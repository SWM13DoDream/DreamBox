// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/Chair.h"
#include "../public/JudgeCharacter.h"
#include "../public/JudgeGameMode.h"
#include "../public/FloatSign.h"
#include "../../common/public/VRCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
AChair::AChair()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	RootComponent = Body;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetRelativeLocation(FVector(0.0f, 30.0f, 70.0f));
	Trigger->SetBoxExtent(FVector(80.0f, 60.0f, 60.0f));
	Trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Trigger->SetupAttachment(RootComponent);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));
	Arrow->SetRelativeLocation(FVector(0.0f, 60.0f, 30.0f));
	Arrow->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	Arrow->SetupAttachment(RootComponent);
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


// Player와 Overlap시 캐릭터의 Movement를 움직이지 못하게 한다
void AChair::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AVRCharacter* JudgePlayer = Cast<AVRCharacter>(OtherActor))
	{
		JudgePlayer->GetCharacterMovement()->ToggleActive();
		OverlappedComp->DestroyComponent();

		AJudgeGameMode* MyMode = Cast<AJudgeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyMode) {
			MyMode->Fade();
		}

		TSubclassOf<AFloatSign> ClassToFind; // Needs to be populated somehow (e.g. by exposing to blueprints as uproperty and setting it there

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);

		for (int i = 0; i < FoundActors.Num(); i++) FoundActors[i]->Destroy();

		FTimerHandle GravityTimerHandle;
		float GravityTime = 1.5f;



		GetWorld()->GetTimerManager().SetTimer(GravityTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				SitChairFunc(OtherActor);

			}), GravityTime, false);	// 반복하려면 false를 true로 변경
		
	}
}

void AChair::SitChairFunc(AActor* OtherActor) {
	if (AVRCharacter* JudgePlayer = Cast<AVRCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))) {
		FVector ArrowLocation = Arrow->K2_GetComponentLocation();
		FRotator ArrowRotation = Arrow->K2_GetComponentRotation();
		JudgePlayer->SetActorLocation(ArrowLocation);
		JudgePlayer->SetActorRotation(ArrowRotation);

		AJudgeGameMode* MyMode = Cast<AJudgeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		MyMode->StartOfTrial.Broadcast();
	}
}

