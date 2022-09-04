// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/ScriptManager.h"
#include "Components/WidgetComponent.h"

// Sets default values
AScriptManager::AScriptManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);
	
	ScriptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SCRIPT_WIDGET"));
	ScriptWidget->SetupAttachment(DefaultSceneRoot);

	VoiceDubbing = CreateDefaultSubobject<UAudioComponent>(TEXT("VOICE_DUBBING"));
	VoiceDubbing->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AScriptManager::BeginPlay()
{
	Super::BeginPlay();
	
	ScriptWidgetRef = Cast<UUserWidget>(ScriptWidget->GetWidget());
}