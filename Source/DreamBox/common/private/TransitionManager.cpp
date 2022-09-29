// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/TransitionManager.h"
#include "../public/PersistentLevelBase.h"
#include "../public/DreamBoxGameModeBase.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"

// Sets default values
ATransitionManager::ATransitionManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	LogoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LOGO_WIDGET"));
	LogoWidgetComponent->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void ATransitionManager::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		LevelScriptRef = Cast<APersistentLevelBase>(GetWorld()->GetLevelScriptActor());
		if (IsValid(LevelScriptRef))
		{
			LevelScriptRef->PreLoadingEnd.AddDynamic(this, &ATransitionManager::PlayLogoDisappearAnim);
		}
	}
	StartLoadTargetMap();
}

bool ATransitionManager::GetLogoAnimationIsSet(bool bIsBeginAnim)
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

void ATransitionManager::StartLoadTargetMap()
{
	if (IsValid(LevelScriptRef))
	{
		if (LevelScriptRef->TransitionOptions.bPlayInitialAnimSequence)
		{
			PlayLogoAnimation(true);
		}

		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			LevelScriptRef->LoadTargetLevel();
		}), 1.25f, false);
	}
}

// Called every frame
void ATransitionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}