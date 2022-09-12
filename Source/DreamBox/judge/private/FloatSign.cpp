// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/FloatSign.h"
#include "../../common/public/VRCharacter.h"
#include "Components/WidgetComponent.h"

// Sets default values
AFloatSign::AFloatSign()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	RootComponent = SceneComponent;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	Box->SetBoxExtent(FVector(120.0f, 60.0f, 60.0f));
	Box->SetupAttachment(RootComponent);

	Screen = CreateDefaultSubobject<UWidgetComponent>(TEXT("SCREEN"));
	Screen->SetRelativeLocation(FVector(70.0f, 0.0f, 30.0f));
	Screen->SetRelativeRotation(FRotator(180.0f, 0.0f, 0.0f));
	Screen->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	Screen->SetDrawSize(FVector2D(600.0f, 500.0f));
	Screen->SetupAttachment(RootComponent);

	Question = CreateDefaultSubobject<UWidgetComponent>(TEXT("QUESTION"));
	Question->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	Question->SetDrawSize(FVector2D(500.0f, 500.0f));
	Question->SetupAttachment(RootComponent);

	Box->OnComponentBeginOverlap.AddDynamic(this, &AFloatSign::OnOverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this, &AFloatSign::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AFloatSign::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatSign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloatSign::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AVRCharacter* JudgePlayer = Cast<AVRCharacter>(OtherActor))
	{
		if (!bToggle) {
			Question->SetVisibility(false);
			bToggle = true;
		}
	}

}

void AFloatSign::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AVRCharacter* JudgePlayer = Cast<AVRCharacter>(OtherActor))
	{
		if (bToggle) {
			Question->SetVisibility(true);
			bToggle = false;
		}
	}
}

