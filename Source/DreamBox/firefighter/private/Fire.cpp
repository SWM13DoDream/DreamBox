// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/Fire.h"
#include "../../common/public/DreamBox.h"
#include "TimerManager.h"

// Sets default values
AFire::AFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Tags = { "Fire" };
	bReplicates = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	FireEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FIRE_EMITTER"));
	FireEmitter->SetupAttachment(DefaultSceneRoot);

	SteamEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Steam_EMITTER"));
	SteamEmitter->SetupAttachment(DefaultSceneRoot);
	SteamEmitter->SetWorldScale3D({ 0.0f, 0.0f, 0.0f });
}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();
	
	//Steam Emitter�� Dynamic Material Instance �ʱ�ȭ
	InitSteamDynamicMaterial();

	if (GetWorld()) GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFire::UpdateEmitterScale(const float Variance)
{
	if (HasAuthority()) //�������� ����Ǵ� ���?
	{
		MulticastUpdateEmitterScale(FireEmitter, Variance); //Multicast ȣ��
		MulticastUpdateEmitterScale(SteamEmitter, (-5.0f) * Variance);
	}
	else //Ŭ���̾�Ʈ���� ����Ǵ� ���?
	{
		ServerRPCUpdateEmitterScale(FireEmitter, Variance); //Server RPC ȣ��
		ServerRPCUpdateEmitterScale(SteamEmitter, (-5.0f) * Variance);
	}
}

void AFire::MulticastUpdateEmitterScale_Implementation(UParticleSystemComponent* Target, const float Variance)
{
	FVector newScale = Target->GetComponentScale() - Variance;
	if (newScale.Y <= 0.0f ||  newScale.Y >= SmokeMaxScale) 
	{
		Target->SetWorldScale3D(newScale.Y <= 0.0f ? FVector(0.0f) : FVector(SmokeMaxScale)); //�̹����� �������� �Ѱ踦 ���� �ʵ��� �����ϸ� ������Ʈ
	}
	else 
	{
		Target->SetWorldScale3D(FMath::VInterpTo(Target->GetComponentScale(), newScale, GetWorld()->DeltaTimeSeconds, 3.0f)); //������ ���� �ڿ������� ������Ʈ
	}
}

void AFire::ServerRPCUpdateEmitterScale_Implementation(UParticleSystemComponent* Target, const float Variance)
{
	MulticastUpdateEmitterScale(Target, Variance); //������ ����� Ŭ���̾�Ʈ�鿡�� ��� ����
}

void AFire::InitSteamDynamicMaterial()
{
	if (SteamMaterialInterface == nullptr) return; //BP���� Mat Interface�� ���������� �ʾҴٸ� ��ȯ
	SteamDynamicMaterial = UMaterialInstanceDynamic::Create(SteamMaterialInterface, GetWorld());
	SteamEmitter->SetMaterial(0, SteamDynamicMaterial);	
	SteamDynamicMaterial->SetScalarParameterValue("Opacity", SteamEmitterInitialOpacity);
	SteamOpacityValue = SteamEmitterInitialOpacity;
}

void AFire::UpdateSteamOpacity()
{
	if (SteamOpacityValue == 0) TryDestroy(); //���Ⱑ ��� �Ҹ��ߴٸ�? �Ҹ� �õ�
	if (HasAuthority())
	{
		MulticastUpdateSteamOpacity(); //�������� ����
	}
	else
	{
		ServerRPCUpdateSteamOpacity(); //Ŭ���̾�Ʈ���� ����
	}
}

void AFire::MulticastUpdateSteamOpacity_Implementation()
{
	if (SteamOpacityValue < 0.0f) return; //SteamOpacity�� ��ȿ���� ���� ���̶��?
	SteamOpacityValue = FMath::Max(0.0f, SteamOpacityValue - SteamEmitterInitialOpacity / SteamEmitterLifeSpan); //���ο� Opacity������ ��ü
	SteamDynamicMaterial->SetScalarParameterValue("Opacity", SteamOpacityValue );// FMath::FInterpTo(SteamOpacityValue + 0.1f, SteamOpacityValue, GetWorld()->DeltaTimeSeconds, 0.5f));
}

void AFire::ServerRPCUpdateSteamOpacity_Implementation()
{
	MulticastUpdateSteamOpacity(); 
}

float AFire::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser == nullptr && !DamageCauser->ActorHasTag("FireHose")) return 0; //DamageCause�� ��ȿ���� �ʰų� FireHose�� �ƴ϶�� return 
	if (FireEmitter->GetComponentScale() == FVector(0.0f) && !bIsReadyToDestroy)
	{
		SetSteamDisappearTimer(); //���� ��� �����ٸ� Destroy
		bIsFireSuppressed = true;
		UpdateMissionDelegate(0, MissionID, 1); //�ӽ� �ڵ�  : 0��° �÷��̾ ������Ʈ
		return 0.0f;
	}
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); //Super Ŭ������ TakeDamage ȣ��
	UpdateEmitterScale(DamageAmount); //������ ��ŭ �̹����� ������ ������Ʈ

	return DamageAmount;
}

void AFire::SetSteamDisappearTimer()
{
	if (bIsReadyToDestroy) return; //�̹� Destroy�� �������̶��
	bIsReadyToDestroy = true; //Destroy�� �غ� �Ǿ��ٰ� üũ
	bIsFireSuppressed = true; //���� ���� �Ǿ����� üũ
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AFire::UpdateSteamOpacity, 1.0f, true); //1�ʸ��� ���Ⱑ ���������� �ݺ�
}

inline void AFire::TryDestroy()
{
	if (SteamOpacityValue > 0.0f) return; //��������� �� ������� Destroy
	if (GetWorldTimerManager().GetTimerRemaining(EmitterUpdateTimerHandle) > 0) //Ÿ�̸Ӱ� �����ִٸ�
	{
		GetWorldTimerManager().ClearTimer(EmitterUpdateTimerHandle); //Ÿ�̸� �ʱ�ȭ
	}
	Destroy();
	return;
}

void AFire::UpdateMissionDelegate(int32 PlayerIdx, int32 TargetMissionID, int32 NewCondition) //115��°��) �� �Ҹ�� ��������Ʈ ȣ�� 
{
	GamemodeRef->UpdateMissionListComponent.Broadcast(PlayerIdx, TargetMissionID, NewCondition);
}
