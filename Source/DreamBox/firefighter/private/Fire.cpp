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

	if (GetWorld()) GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFire::UpdateEmitterScale(const float Variance)
{
	if (HasAuthority()) //서버에서 실행되는 경우?
	{
		MulticastUpdateEmitterScale(FireEmitter, Variance); //Multicast 호출
		MulticastUpdateEmitterScale(SteamEmitter, (-5.0f) * Variance);
	}
	else //클라이언트에서 실행되는 경우?
	{
		ServerRPCUpdateEmitterScale(FireEmitter, Variance); //Server RPC 호출
		ServerRPCUpdateEmitterScale(SteamEmitter, (-5.0f) * Variance);
	}
}

void AFire::MulticastUpdateEmitterScale_Implementation(UParticleSystemComponent* Target, const float Variance)
{
	FVector newScale = Target->GetComponentScale() - Variance;
	if (newScale.Y <= 0.0f ||  newScale.Y >= SmokeMaxScale) 
	{
		Target->SetWorldScale3D(newScale.Y <= 0.0f ? FVector(0.0f) : FVector(SmokeMaxScale)); //이미터의 스케일이 한계를 넘지 않도록 방지하며 업데이트
	}
	else 
	{
		Target->SetWorldScale3D(FMath::VInterpTo(Target->GetComponentScale(), newScale, GetWorld()->DeltaTimeSeconds, 3.0f)); //보간을 통해 자연스럽게 업데이트
	}
}

void AFire::ServerRPCUpdateEmitterScale_Implementation(UParticleSystemComponent* Target, const float Variance)
{
	MulticastUpdateEmitterScale(Target, Variance); //서버와 연결된 클라이언트들에게 모두 실행
}

void AFire::InitSteamDynamicMaterial()
{
	if (SteamMaterialInterface == nullptr) return; //BP에서 Mat Interface를 지정해주지 않았다면 반환
	SteamDynamicMaterial = UMaterialInstanceDynamic::Create(SteamMaterialInterface, GetWorld());
	SteamEmitter->SetMaterial(0, SteamDynamicMaterial);	
	SteamDynamicMaterial->SetScalarParameterValue("Opacity", SteamEmitterInitialOpacity);
	SteamOpacityValue = SteamEmitterInitialOpacity;
}

void AFire::UpdateSteamOpacity()
{
	if (SteamOpacityValue == 0) TryDestroy(); //연기가 모두 소멸했다면? 소멸 시도
	if (HasAuthority())
	{
		MulticastUpdateSteamOpacity(); //서버에서 실행
	}
	else
	{
		ServerRPCUpdateSteamOpacity(); //클라이언트에서 실행
	}
}

void AFire::MulticastUpdateSteamOpacity_Implementation()
{
	if (SteamOpacityValue < 0.0f) return; //SteamOpacity가 유효하지 않은 값이라면?
	SteamOpacityValue = FMath::Max(0.0f, SteamOpacityValue - SteamEmitterInitialOpacity / SteamEmitterLifeSpan); //새로운 Opacity값으로 대체
	SteamDynamicMaterial->SetScalarParameterValue("Opacity", SteamOpacityValue );// FMath::FInterpTo(SteamOpacityValue + 0.1f, SteamOpacityValue, GetWorld()->DeltaTimeSeconds, 0.5f));
}

void AFire::ServerRPCUpdateSteamOpacity_Implementation()
{
	MulticastUpdateSteamOpacity(); 
}

float AFire::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageCauser == nullptr && !DamageCauser->ActorHasTag("FireHose")) return 0; //DamageCause이 유효하지 않거나 FireHose가 아니라면 return 
	if (FireEmitter->GetComponentScale() == FVector(0.0f) && !bIsReadyToDestroy)
	{
		SetSteamDisappearTimer(); //불이 모두 꺼졌다면 Destroy
		bIsFireSuppressed = true;
		UpdateMissionDelegate(0, MissionID, 1); //임시 코드  : 0번째 플레이어만 업데이트
		return 0.0f;
	}
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); //Super 클래스의 TakeDamage 호출
	UpdateEmitterScale(DamageAmount); //데미지 만큼 이미터의 스케일 업데이트

	return DamageAmount;
}

void AFire::SetSteamDisappearTimer()
{
	if (bIsReadyToDestroy) return; //이미 Destroy가 진행중이라면
	bIsReadyToDestroy = true; //Destroy될 준비가 되었다고 체크
	bIsFireSuppressed = true; //불이 진압 되었음을 체크
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AFire::UpdateSteamOpacity, 1.0f, true); //1초마다 연기가 옅어지도록 반복
}

inline void AFire::TryDestroy()
{
	if (SteamOpacityValue > 0.0f) return; //수증기까지 다 사라지면 Destroy
	if (GetWorldTimerManager().GetTimerRemaining(EmitterUpdateTimerHandle) > 0) //타이머가 남아있다면
	{
		GetWorldTimerManager().ClearTimer(EmitterUpdateTimerHandle); //타이머 초기화
	}
	Destroy();
	return;
}

void AFire::UpdateMissionDelegate(int32 PlayerIdx, int32 TargetMissionID, int32 NewCondition) //115번째줄) 불 소멸시 델리게이트 호출 
{
	GamemodeRef->UpdateMissionListComponent.Broadcast(PlayerIdx, TargetMissionID, NewCondition);
}
