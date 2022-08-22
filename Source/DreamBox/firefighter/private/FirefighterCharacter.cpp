// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/FirefighterCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "../public/FirefighterGamemode.h"
#include "../public/FireHose.h"

// Sets default values
AFirefighterCharacter::AFirefighterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FireHose = CreateDefaultSubobject<UChildActorComponent>(TEXT("FIRE_HOSE"));
	FireHose->SetupAttachment(FollowingCamera);

	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FLASHLIGHT"));
	FlashLight->SetupAttachment(FollowingCamera);
	FlashLight->Intensity = 10000.0f;
	FlashLight->AttenuationRadius = 4000.0f;
	FlashLight->InnerConeAngle = 20.0f;
	FlashLight->OuterConeAngle = 28.0f;

	RescueSocket = CreateDefaultSubobject<USpringArmComponent>(TEXT("RESCUE_SOCKET"));
	RescueSocket->SetupAttachment(FollowingCamera);
	RescueSocket->SetRelativeRotation(FQuat(0.0f, 0.0f, -90.0f, 0.0f));
	RescueSocket->TargetArmLength = 50.0f;
	RescueSocket->bEnableCameraLag = true;
}

// Called when the game starts or when spawned
void AFirefighterCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	if (GetWorld()) GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
	//if(IsValid(GamemodeRef)) GamemodeRef->UpdateMissionList() //BP 코드에서 이주 예정@@@
}

// Called every frame
void AFirefighterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirefighterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFirefighterCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFirefighterCharacter::StopFire);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AFirefighterCharacter::TryInteraction);
}

void AFirefighterCharacter::TryInteraction()
{
	if (bIsCarrying || !GetIsReadyToInteraction()) return; //상호작용 불가능 : 업고 있거나 집고 있는 상황

	switch (InteractionType) //상호작용 타입에 따라 구분
	{
	case EFirefighterInteractionType::E_CARRY :
		GamemodeRef->PlayFadeInOutAnimation.Broadcast(0); //PlayerID는 임시로 0
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&](){
			CarryInjuredCharacter(); //FadeIn 중간에 캐릭터를 업음
		}), 0.75f, false); 
		break;
	case EFirefighterInteractionType::E_PICK :
		
		break;
	case EFirefighterInteractionType::E_INVESTIGATE :
		GamemodeRef->PlayFadeInOutAnimation.Broadcast(0); //PlayerID는 임시로 0
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			InvestigateCauseOfFire(); //FadeIn 중간에 캐릭터를 업음
			}), 0.75f, false);
		break;
	default:
		break;
	}
}

void AFirefighterCharacter::Fire()
{
	if (!IsValid(FireHose->GetChildActor())) return;
	Cast<AFireHose>(FireHose->GetChildActor())->ActivateEmitter(); //소유한 호스의 나이아가라 이미터를 활성화
}

void AFirefighterCharacter::StopFire()
{
	if (!IsValid(FireHose->GetChildActor())) return;
	Cast<AFireHose>(FireHose->GetChildActor())->DeactivateEmitter();  //소유한 호스의 나이아가라 이미터를 비활성화
}

void AFirefighterCharacter::InvestigateCauseOfFire()
{
	if (!IsValid(CauseOfFireRef) || !GetIsReadyToInteraction()) return; 
	CauseOfFireRef->Destroy();
}

void AFirefighterCharacter::CarryInjuredCharacter()
{
	if (!IsValid(InjuredCharacterRef) && !InjuredCharacterRef->GetIsBeingRescued()) return; //타겟이 유효하지 않거나 이미 구조되고 있는 캐릭터라면
	if (bIsCarrying || !bIsReadyToInteraction) return; //이미 업고 있거나 상호작용 할 준비가 되지 않았다면

	InjuredCharacterRef->SetIsBeingRescued(true); //타겟 캐릭터가 구조중(업는중)이라고 체크
	InjuredCharacterRef->SetCharacterCollisionState(false); //콜리전 제거
	InjuredCharacterRef->GetRootComponent()->AttachToComponent(RescueSocket, FAttachmentTransformRules::SnapToTargetNotIncludingScale); //붙임
	InjuredCharacterRef->GetRootComponent()->SetRelativeLocation({ 20.0f, 40.0f, 30.0f }); //상대 위치와 로테이션 지정
	InjuredCharacterRef->GetRootComponent()->SetRelativeRotation({ 0.0f, 0.0f, 0.0f });
	
	SetIsCarrying(true); //업고있다고 체크
	SetIsReadyToInteraction(false); //상호작용 불가능
}

void AFirefighterCharacter::PutInjuredCharacter()
{
	if (!IsValid(InjuredCharacterRef)) return; // 타겟 유효성 체크
	InjuredCharacterRef->Destroy(); //타겟 캐릭터 소멸
	ResetInteractionState(); //인터랙션 설정값들 초기화 
}

void AFirefighterCharacter::SetCauseOfFireRef(ACauseOfFire* NewCauseOfFire)
{
	CauseOfFireRef = NewCauseOfFire;
}

void AFirefighterCharacter::SetInjuredCharacterRef(AInjuredCharacter* NewInjuredCharacter)
{
	InjuredCharacterRef = NewInjuredCharacter;
}

void AFirefighterCharacter::SetInteractionType(EFirefighterInteractionType NewType)
{
	InteractionType = NewType;
}

void AFirefighterCharacter::SetIsReadyToInteraction(bool NewState)
{
	bIsReadyToInteraction = NewState;
}

void AFirefighterCharacter::SetIsCarrying(bool NewState)
{
	bIsCarrying = NewState;
}

void AFirefighterCharacter::ResetInteractionState()
{
	SetInjuredCharacterRef(nullptr); //Carry 타겟 캐릭터 지움
	SetInteractionType(EFirefighterInteractionType::E_NONE); //상호작용 타입 None
	SetIsCarrying(false); //업고 있지 않음을 체크
	SetIsReadyToInteraction(false); //상호작용할 준비가 되어있지 않음을 체크
}
