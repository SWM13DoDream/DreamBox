// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/FireHose.h"
#include "Kismet/GameplayStatics.h"
#include "../../common/public/DreamBox.h"

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
	WaterEmitter->Deactivate();
}

// Called when the game starts or when spawned
void AFireHose::BeginPlay()
{
	Super::BeginPlay();

	WaterEmitter->SetNiagaraVariableObject("User.BP_Callback", this); //나이아가라 콜백 객체를 지정
}

// Called every frame
void AFireHose::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireHose::ActivateEmitter()
{
	WaterEmitter->Activate(); //물을 켬 : 나이아가라를 활성화
}

void AFireHose::DeactivateEmitter()
{
	WaterEmitter->Deactivate(); //물을 끔 : 나이아가라 비활성화 
}

void AFireHose::MulticastApplyDamageToFire_Implementation(FVector Location)
{
	//해당 지점에 FireHoseDamage 만큼의 범위 데미지를 가함
	UGameplayStatics::ApplyRadialDamage(GetWorld(), FireHoseDamage, Location, 5.0f, UDamageType::StaticClass(), {}, this, nullptr); 
}

void AFireHose::ServerRPCApplyDamageToFire_Implementation(FVector Location)
{
	MulticastApplyDamageToFire(Location);
}