// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/FireHose.h"
#include "../public/FirefighterCharacter.h"
#include "../public/FirefighterGamemode.h"
#include "Components/ChildActorComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
AFireHose::AFireHose()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Tags = { "FireHose" };

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	FireHoseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FIRE_HOSE"));
	FireHoseMesh->SetupAttachment(DefaultSceneRoot);

	WaterEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FIRE_EMITTER"));
	WaterEmitter->SetupAttachment(FireHoseMesh);
	WaterEmitter->SetNiagaraVariableObject("User.BP_Callback", this);
	WaterEmitter->SetRelativeLocation({ 0.0f, 0.0f, 0.0f});
	WaterEmitter->Deactivate();

	FirehoseSound = CreateDefaultSubobject<UAudioComponent>(TEXT("FIRE_HOSE_SOUND"));
	FirehoseSound->SetupAttachment(FireHoseMesh);
	FirehoseSound->bAutoActivate = false;
	FirehoseSound->SetRelativeLocation(FVector(0.0f));
}

// Called when the game starts or when spawned
void AFireHose::BeginPlay()
{
	Super::BeginPlay();

	WaterEmitter->SetNiagaraVariableObject("User.BP_Callback", this); //���̾ư��� �ݹ� ��ü�� ����
	if (GetWorld())
	{
		if (IsValid(GetWorld()->GetAuthGameMode<AFirefighterGamemode>()))
		{
			GetWorld()->GetAuthGameMode<AFirefighterGamemode>()->ShowScriptWithID.AddDynamic(this, &AFireHose::ScriptEventWithID);
			GetWorld()->GetAuthGameMode<AFirefighterGamemode>()->ShowScriptWithString.AddDynamic(this, &AFireHose::ScriptEventWithString);
		}
	}
}

// Called every frame
void AFireHose::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireHose::ActivateEmitter()
{
	WaterEmitter->Activate(); //���� �� : ���̾ư��� Ȱ��ȭ
	FirehoseSound->Activate();
}

void AFireHose::DeactivateEmitter()
{
	WaterEmitter->Deactivate(); //���� �� : ���̾ư��� ��Ȱ��ȭ 
	FirehoseSound->Deactivate();
}

void AFireHose::ScriptEventWithID(int32 PlayerID, int32 ScriptID)
{
	DeactivateEmitter();
}

void AFireHose::ScriptEventWithString(int32 PlayerID, FString Script)
{
	DeactivateEmitter();
}

void AFireHose::ApplyDamageToFire(FVector Location)
{	
	//�ش� ������ FireHoseDamage ��ŭ�� ���� �������� ����
	UGameplayStatics::ApplyRadialDamage(GetWorld(), FireHoseDamage, Location, 5.0f, UDamageType::StaticClass(), {}, this, nullptr);
}

void AFireHose::ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem)
{
	for (const FBasicParticleData& ParticleData : Data)
	{
		ApplyDamageToFire(ParticleData.Position);
	}
}
