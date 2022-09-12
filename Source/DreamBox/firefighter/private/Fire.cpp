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
	
	//Steam Emitter의 Dynamic Material Instance 초기화
	InitSteamDynamicMaterial();

	//Gamemode의 레퍼런스를 초기화
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
		Target->SetWorldScale3D(newScale.Y <= 0.0f ? FVector(0.0f) : FVector(SmokeMaxScale)); //이미터의 스케일이 한계를 넘지 않도록 방지하며 업데이트
	}
	else
	{
		Target->SetWorldScale3D(FMath::VInterpTo(Target->GetComponentScale(), newScale, GetWorld()->DeltaTimeSeconds, 3.0f)); //보간을 통해 자연스럽게 업데이트
	}
}

void AFire::InitSteamDynamicMaterial()
{
	if (SteamMaterialInterface == nullptr) return; //BP에서 Mat Interface를 지정해주지 않았다면 반환
	
	//지정한 Steam Emitter에 대한 Material Instance를 생성하고, 초기 값을 지정
	SteamDynamicMaterial = UMaterialInstanceDynamic::Create(SteamMaterialInterface, GetWorld());
	SteamEmitter->SetMaterial(0, SteamDynamicMaterial);	
	SteamDynamicMaterial->SetScalarParameterValue("Opacity", SteamEmitterInitialOpacity);
	SteamOpacityValue = SteamEmitterInitialOpacity;
}

void AFire::UpdateSteamOpacity()
{
	if (SteamOpacityValue <= 0.0f) TryDestroyFire(); //연기가 모두 소멸했다면? 소멸 시도
	
	SteamOpacityValue = FMath::Max(0.0f, SteamOpacityValue - SteamEmitterInitialOpacity / SteamEmitterLifeSpan); //새로운 Opacity값으로 대체
	SteamDynamicMaterial->SetScalarParameterValue("Opacity", SteamOpacityValue);
}

float AFire::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!IsValid(DamageCauser) && !DamageCauser->ActorHasTag("FireHose")) return 0; //DamageCause이 유효하지 않거나 FireHose가 아니라면 return 
	if (CheckAndUpdateSuppressedState()) return 0;

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); //Super 클래스의 TakeDamage 호출
	UpdateEmitterScale(FireEmitter, DamageAmount); //Multicast 호출
	UpdateEmitterScale(SteamEmitter, (-5.0f) * DamageAmount);

	return DamageAmount;
}

void AFire::SetSteamDisappearTimer()
{
	if (bIsReadyToDestroy) return; //이미 Destroy가 진행중이라면
	bIsReadyToDestroy = true; //Destroy될 준비가 되었다고 체크
	bIsFireSuppressed = true; //불이 진압 되었음을 체크
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AFire::UpdateSteamOpacity, 1.0f, true); //1초마다 연기가 옅어지도록 반복
}

void AFire::TryDestroyFire()
{
	if (SteamOpacityValue > 0.0f) return; //수증기까지 다 사라지면 Destroy
	if (GetWorldTimerManager().GetTimerRemaining(EmitterUpdateTimerHandle) <= 0.0f) return; //타이머가 남아있다면
	
	GetWorldTimerManager().ClearTimer(EmitterUpdateTimerHandle); //타이머 초기화
	Destroy();
}

bool AFire::CheckAndUpdateSuppressedState()
{
	if (FireEmitter->GetComponentScale().Y > 0.05f || bIsReadyToDestroy) return false;
	
	SetSteamDisappearTimer(); //불이 모두 꺼졌다면 Destroy
	FireEmitter->SetWorldScale3D(FVector(0.0f)); //근사치에 가까운 값을 0으로 지정
	BlockingVolume->SetCollisionProfileName(FName("OverlapAll")); //블로킹 볼륨의 콜리전을 해제
	bIsFireSuppressed = true; //불 진압 여부를 나타내는 변수를 업데이트
	FireGuideMesh->SetVisibility(false); //FireGuideMesh를 Hidden으로 지정
	
	GamemodeRef->UpdateMissionList.Broadcast(0, MissionID, 1); //미션 업데이트
	return true;
}
