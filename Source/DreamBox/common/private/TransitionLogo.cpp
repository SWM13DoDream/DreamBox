// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/TransitionLogo.h"
#include "../public/PersistentLevelBase.h"
#include "../public/DreamBoxGameModeBase.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"

// Sets default values
ATransitionLogo::ATransitionLogo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	LogoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LOGO_WIDGET"));
	LogoWidgetComponent->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void ATransitionLogo::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		LevelScriptRef = Cast<APersistentLevelBase>(GetWorld()->GetLevelScriptActor());
		if (IsValid(LevelScriptRef))
		{
			LevelScriptRef->LoadingDoneEvent.AddDynamic(this, &ATransitionLogo::PlayLogoDisappearAnim);
		}
	}
	StartLoadTargetMap();
}

bool ATransitionLogo::GetLogoAnimationIsSet(bool bIsBeginAnim)
{
	if (IsValid(LevelScriptRef))
	{
		if (bIsBeginAnim)
		{
			return LevelScriptRef->TransitionOptions.bPlayInitialAnimSequence;
		}
		else
		{
			return LevelScriptRef->TransitionOptions.bPlayFinalAnimSequence;
		}
	}
	return false;
}

void ATransitionLogo::StartLoadTargetMap()
{
	PlayLogoAnimation(true);

	if (IsValid(LevelScriptRef))
	{
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			LevelScriptRef->LoadTargetLevelWithTransition();
		}), 1.25f, false);
	}
}

// Called every frame
void ATransitionLogo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}