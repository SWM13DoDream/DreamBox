// Fill out your copyright notice in the Description page of Project Settings.

#include "FireHose.h"
#include "DreamBox.h"

// Sets default values
AFireHose::AFireHose()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Tags = { "FireHose" };

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	WaterEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FIRE_EMITTER"));
	WaterEmitter->SetupAttachment(DefaultSceneRoot);
	WaterEmitter->SetRelativeLocation({ 0.0f, 0.0f, 0.0f});
}

// Called when the game starts or when spawned
void AFireHose::BeginPlay()
{
	Super::BeginPlay();

	WaterEmitter->SetNiagaraVariableObject("User.BP_Callback", this);
}

// Called every frame
void AFireHose::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

