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
	
	//Steam Emitter의 Dynamic Material Instance 초기화
	InitSteamDynamicMaterial();
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) //서버에서 실행되는 경우?
	{
		MulticastUpdateEmitterScale(FireEmitter, { FireScaleSize, FireScaleSize, FireScaleSize }); //Multicast 호출
		MulticastUpdateEmitterScale(SteamEmitter, { SteamScaleSize, SteamScaleSize, SteamScaleSize });
	}
	else //클라이언트에서 실행되는 경우?
	{
		ServerRPCUpdateEmitterScale(FireEmitter, { FireScaleSize, FireScaleSize, FireScaleSize }); //Server RPC 호출
		ServerRPCUpdateEmitterScale(SteamEmitter, { SteamScaleSize, SteamScaleSize, SteamScaleSize });
	}

	if (IsReadyToDestroy) //Destroy될 준비가 되었다면? (불이 모두 꺼졌다면)
	{
		TryDestroy(); //Destroy를 시도
	}
}

void AFire::MulticastUpdateEmitterScale_Implementation(UParticleSystemComponent* Target, const FVector& NewScale)
{
	if (NewScale.Y < 0.0f || NewScale.Y > 3.0f) return;
	Target->SetWorldScale3D(FMath::VInterpTo(Target->GetComponentScale(), NewScale, 0.1f, 0.25f)); //매 Tick 마다 FireScaleSize를 업데이트한다.
}

void AFire::ServerRPCUpdateEmitterScale_Implementation(UParticleSystemComponent* Target, const FVector& NewScale)
{
	MulticastUpdateEmitterScale(Target, NewScale); //서버와 연결된 클라이언트들에게 모두 실행
}

void AFire::InitSteamDynamicMaterial()
{
	if (SteamMaterialInterface == nullptr) return; //BP에서 Mat Interface를 지정해주지 않았다면 반환
	SteamDynamicMaterial = UMaterialInstanceDynamic::Create(SteamMaterialInterface, GetWorld());
	SteamEmitter->SetMaterial(0, SteamDynamicMaterial);	
}

void AFire::MulticastUpdateSteamOpacity_Implementation()
{
	if (SteamOpacityValue < 0.0f) return; //SteamOpacity가 유효하지 않은 값이라면?
	SteamOpacityValue -= 0.01f; //새로운 Opacity값으로 대체
	SteamDynamicMaterial->SetScalarParameterValue("Opacity", FMath::FInterpTo(SteamOpacityValue+0.1f, SteamOpacityValue, 0.05f, 0.5f));  
}

void AFire::ServerRPCUpdateSteamOpacity_Implementation()
{
	MulticastUpdateSteamOpacity(); 
}

float AFire::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser == nullptr && !DamageCauser->ActorHasTag("FireHose")) return 0; //DamageCause이 유효하지 않거나 FireHose가 아니라면 return 
	if (FireScaleSize == 0) SetSteamDisappearTimer(); //불이 모두 꺼졌다면 Destroy

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); //Super 클래스의 TakeDamage 호출

	FireScaleSize = FMath::Max(0.0f, FireScaleSize - DamageAmount * FMath::FRandRange(1.25f, 1.75f));  //FireScale을 DamageAmount만큼 뺌, (자연스러운 전환위해 rand값 추가)
	SteamScaleSize = FMath::Min(3.0f, SteamScaleSize + DamageAmount * FMath::FRandRange(3.0f, 5.0f));  //SteamScale값도 위와 마찬가지로 업데이트

	return DamageAmount;
}

void AFire::SetSteamDisappearTimer()
{
	if (IsReadyToDestroy) return; //이미 Destroy가 진행중이라면
	IsReadyToDestroy = true; //Destroy될 준비가 되었다고 체크

	FTimerHandle DestroyTimerHandle; //DestroyTimer 핸들
	float SteamLifeSpan = 100.0f; //연기의 Life (특정 시간만큼 Opacity 업데이트)
	if(HasAuthority())
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AFire::MulticastUpdateSteamOpacity, 0.5f, true, 0.0f); //타이머 설정
	else
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AFire::ServerRPCUpdateSteamOpacity, 0.5f, true, 0.0f); //타이머 설정
}

void AFire::TryDestroy()
{
	if (SteamOpacityValue > 0) return; //수증기까지 다 사라지면 Destroy
	Destroy();
	return;
}