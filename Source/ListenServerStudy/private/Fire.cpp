// Fill out your copyright notice in the Description page of Project Settings.

#include "Fire.h"
#include "ListenServerStudy.h"

// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Tags = { "Fire" };

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	FireEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FIRE_EMITTER"));
	FireEmitter->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FireScaleSize > 0.0f) 
		this->SetActorScale3D({ FireScaleSize, FireScaleSize, FireScaleSize }); //매 Tick 마다 FireScaleSize를 업데이트한다.
	else Destroy();
}

float AFire::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser == nullptr && !DamageCauser->ActorHasTag("FireHose")) return 0; //DamageCause이 유효하지 않거나 FireHose가 아니라면 return 
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); //Super 클래스의 TakeDamage 호출
	FireScaleSize -= DamageAmount;  //FireScale을 DamageAmount만큼 뺌
	return DamageAmount;
}

