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
		this->SetActorScale3D({ FireScaleSize, FireScaleSize, FireScaleSize }); //�� Tick ���� FireScaleSize�� ������Ʈ�Ѵ�.
	else Destroy();
}

float AFire::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser == nullptr && !DamageCauser->ActorHasTag("FireHose")) return 0; //DamageCause�� ��ȿ���� �ʰų� FireHose�� �ƴ϶�� return 
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); //Super Ŭ������ TakeDamage ȣ��
	FireScaleSize -= DamageAmount;  //FireScale�� DamageAmount��ŭ ��
	return DamageAmount;
}

