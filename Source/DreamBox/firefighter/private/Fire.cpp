<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/Fire.h"
#include "../public/FirefighterGamemode.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"

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

	SteamEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("STEAM_EMITTER"));
	SteamEmitter->SetupAttachment(DefaultSceneRoot);
	SteamEmitter->SetWorldScale3D(FVector(0.0f));

	BlockingVolume = CreateDefaultSubobject<USphereComponent>(TEXT("BLOCKING_VOLUME"));
	BlockingVolume->SetupAttachment(DefaultSceneRoot);
	BlockingVolume->SetRelativeLocation(FVector(0.0f));
	BlockingVolume->SetWorldScale3D(FVector(5.0f));

	FireGuideMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FIRE_GUIDE_MESH"));
	FireGuideMesh->SetupAttachment(DefaultSceneRoot);
}

// Called when the game starts or when spawned
void AFire::BeginPlay()
{
	Super::BeginPlay();
	
	//Steam Emitter�� Dynamic Material Instance �ʱ�ȭ
	InitSteamDynamicMaterial();

	//Gamemode�� ���۷����� �ʱ�ȭ
	if (GetWorld()) GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFire::UpdateEmitterScale(UParticleSystemComponent* Target, const float Variance)
{
	FVector newScale = Target->GetComponentScale() - Variance;
	if (newScale.Y <= 0.0f || newScale.Y >= SmokeMaxScale)
	{
		Target->SetWorldScale3D(newScale.Y <= 0.0f ? FVector(0.0f) : FVector(SmokeMaxScale)); //�̹����� �������� �Ѱ踦 ���� �ʵ��� �����ϸ� ������Ʈ
	}
	else
	{
		Target->SetWorldScale3D(FMath::VInterpTo(Target->GetComponentScale(), newScale, GetWorld()->DeltaTimeSeconds, 3.0f)); //������ ���� �ڿ������� ������Ʈ
	}
}

void AFire::InitSteamDynamicMaterial()
{
	if (SteamMaterialInterface == nullptr) return; //BP���� Mat Interface�� ���������� �ʾҴٸ� ��ȯ
	
	//������ Steam Emitter�� ���� Material Instance�� �����ϰ�, �ʱ� ���� ����
	SteamDynamicMaterial = UMaterialInstanceDynamic::Create(SteamMaterialInterface, GetWorld());
	SteamEmitter->SetMaterial(0, SteamDynamicMaterial);	
	SteamDynamicMaterial->SetScalarParameterValue("Opacity", SteamEmitterInitialOpacity);
	SteamOpacityValue = SteamEmitterInitialOpacity;
}

void AFire::UpdateSteamOpacity()
{
	if (SteamOpacityValue <= 0.0f) TryDestroyFire(); //���Ⱑ ��� �Ҹ��ߴٸ�? �Ҹ� �õ�
	
	SteamOpacityValue = FMath::Max(0.0f, SteamOpacityValue - SteamEmitterInitialOpacity / SteamEmitterLifeSpan); //���ο� Opacity������ ��ü
	SteamDynamicMaterial->SetScalarParameterValue("Opacity", SteamOpacityValue);
}

float AFire::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!IsValid(DamageCauser) && !DamageCauser->ActorHasTag("FireHose")) return 0; //DamageCause�� ��ȿ���� �ʰų� FireHose�� �ƴ϶�� return 
	if (CheckAndUpdateSuppressedState()) return 0;

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); //Super Ŭ������ TakeDamage ȣ��
	UpdateEmitterScale(FireEmitter, DamageAmount); //Multicast ȣ��
	UpdateEmitterScale(SteamEmitter, (-5.0f) * DamageAmount);

	return DamageAmount;
}

void AFire::SetSteamDisappearTimer()
{
	if (bIsReadyToDestroy) return; //�̹� Destroy�� �������̶��
	bIsReadyToDestroy = true; //Destroy�� �غ� �Ǿ��ٰ� üũ
	bIsFireSuppressed = true; //���� ���� �Ǿ����� üũ
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AFire::UpdateSteamOpacity, 1.0f, true); //1�ʸ��� ���Ⱑ ���������� �ݺ�
}

void AFire::TryDestroyFire()
{
	if (SteamOpacityValue > 0.0f) return; //��������� �� ������� Destroy
	if (GetWorldTimerManager().GetTimerRemaining(EmitterUpdateTimerHandle) <= 0.0f) return; //Ÿ�̸Ӱ� �����ִٸ�
	
	GetWorldTimerManager().ClearTimer(EmitterUpdateTimerHandle); //Ÿ�̸� �ʱ�ȭ
	Destroy();
}

bool AFire::CheckAndUpdateSuppressedState()
{
	if (FireEmitter->GetComponentScale().Y > 0.05f || bIsReadyToDestroy) return false;
	
	SetSteamDisappearTimer(); //���� ��� �����ٸ� Destroy
	FireEmitter->SetWorldScale3D(FVector(0.0f)); //�ٻ�ġ�� ����� ���� 0���� ����
	BlockingVolume->SetCollisionProfileName(FName("OverlapAll")); //���ŷ ������ �ݸ����� ����
	bIsFireSuppressed = true; //�� ���� ���θ� ��Ÿ���� ������ ������Ʈ
	FireGuideMesh->SetVisibility(false); //FireGuideMesh�� Hidden���� ����
	
	GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, 1); //�̼� ������Ʈ
	return true;
}
=======
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
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) //�������� ����Ǵ� ���?
	{
		MulticastUpdateEmitterScale(FireEmitter, { FireScaleSize, FireScaleSize, FireScaleSize }); //Multicast ȣ��
		MulticastUpdateEmitterScale(SteamEmitter, { SteamScaleSize, SteamScaleSize, SteamScaleSize });
	}
	else //Ŭ���̾�Ʈ���� ����Ǵ� ���?
	{
		ServerRPCUpdateEmitterScale(FireEmitter, { FireScaleSize, FireScaleSize, FireScaleSize }); //Server RPC ȣ��
		ServerRPCUpdateEmitterScale(SteamEmitter, { SteamScaleSize, SteamScaleSize, SteamScaleSize });
	}

	if (IsReadyToDestroy) //Destroy�� �غ� �Ǿ��ٸ�? (���� ��� �����ٸ�)
	{
		TryDestroy(); //Destroy�� �õ�
	}
}

void AFire::MulticastUpdateEmitterScale_Implementation(UParticleSystemComponent* Target, const FVector& NewScale)
{
	if (NewScale.Y < 0.0f || NewScale.Y > 3.0f) return;
	Target->SetWorldScale3D(FMath::VInterpTo(Target->GetComponentScale(), NewScale, 0.1f, 0.25f)); //�� Tick ���� FireScaleSize�� ������Ʈ�Ѵ�.
}

void AFire::ServerRPCUpdateEmitterScale_Implementation(UParticleSystemComponent* Target, const FVector& NewScale)
{
	MulticastUpdateEmitterScale(Target, NewScale); //������ ����� Ŭ���̾�Ʈ�鿡�� ��� ����
}

void AFire::InitSteamDynamicMaterial()
{
	if (SteamMaterialInterface == nullptr) return; //BP���� Mat Interface�� ���������� �ʾҴٸ� ��ȯ
	SteamDynamicMaterial = UMaterialInstanceDynamic::Create(SteamMaterialInterface, GetWorld());
	SteamEmitter->SetMaterial(0, SteamDynamicMaterial);	
}

void AFire::MulticastUpdateSteamOpacity_Implementation()
{
	if (SteamOpacityValue < 0.0f) return; //SteamOpacity�� ��ȿ���� ���� ���̶��?
	SteamOpacityValue -= 0.01f; //���ο� Opacity������ ��ü
	SteamDynamicMaterial->SetScalarParameterValue("Opacity", FMath::FInterpTo(SteamOpacityValue+0.1f, SteamOpacityValue, 0.05f, 0.5f));  
}

void AFire::ServerRPCUpdateSteamOpacity_Implementation()
{
	MulticastUpdateSteamOpacity(); 
}

float AFire::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser == nullptr && !DamageCauser->ActorHasTag("FireHose")) return 0; //DamageCause�� ��ȿ���� �ʰų� FireHose�� �ƴ϶�� return 
	if (FireScaleSize == 0) SetSteamDisappearTimer(); //���� ��� �����ٸ� Destroy

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); //Super Ŭ������ TakeDamage ȣ��

	FireScaleSize = FMath::Max(0.0f, FireScaleSize - DamageAmount * FMath::FRandRange(1.25f, 1.75f));  //FireScale�� DamageAmount��ŭ ��, (�ڿ������� ��ȯ���� rand�� �߰�)
	SteamScaleSize = FMath::Min(3.0f, SteamScaleSize + DamageAmount * FMath::FRandRange(3.0f, 5.0f));  //SteamScale���� ���� ���������� ������Ʈ

	return DamageAmount;
}

void AFire::SetSteamDisappearTimer()
{
	if (IsReadyToDestroy) return; //�̹� Destroy�� �������̶��
	IsReadyToDestroy = true; //Destroy�� �غ� �Ǿ��ٰ� üũ

	FTimerHandle DestroyTimerHandle; //DestroyTimer �ڵ�
	float SteamLifeSpan = 100.0f; //������ Life (Ư�� �ð���ŭ Opacity ������Ʈ)
	if(HasAuthority())
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AFire::MulticastUpdateSteamOpacity, 0.5f, true, 0.0f); //Ÿ�̸� ����
	else
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AFire::ServerRPCUpdateSteamOpacity, 0.5f, true, 0.0f); //Ÿ�̸� ����
}

void AFire::TryDestroy()
{
	if (SteamOpacityValue > 0) return; //��������� �� ������� Destroy
	Destroy();
	return;
}
>>>>>>> 37667fc1c8371a3dc5717464c7a857d6d5968402
