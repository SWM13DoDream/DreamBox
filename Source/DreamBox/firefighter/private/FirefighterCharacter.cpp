// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/FirefighterCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "../public/FirefighterGamemode.h"
#include "../public/FireHose.h"

// Sets default values
AFirefighterCharacter::AFirefighterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Tags = { "Player" };

	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VR_ORIGIN"));
	VROrigin->SetupAttachment(RootComponent);

	SpectatorRef = CreateDefaultSubobject<USceneComponent>(TEXT("SpectatorRef"));
	SpectatorRef->SetupAttachment(VROrigin);

	FollowingCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FOLLOWING_CAMERA"));
	FollowingCamera->SetupAttachment(VROrigin);
	FollowingCamera->SetRelativeLocation({ 30.0f, 0.0f, 60.0f });
	FollowingCamera->bUsePawnControlRotation = true; 

	FireHose = CreateDefaultSubobject<UChildActorComponent>(TEXT("FIRE_HOSE"));
	FireHose->SetupAttachment(FollowingCamera);

	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FLASHLIGHT"));
	FlashLight->SetupAttachment(FollowingCamera);
	FlashLight->Intensity = 10000.0f;
	FlashLight->AttenuationRadius = 4000.0f;
	FlashLight->InnerConeAngle = 20.0f;
	FlashLight->OuterConeAngle = 28.0f;
}

// Called when the game starts or when spawned
void AFirefighterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(GetWorld()) GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
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

	//입력을 함수와 바인딩
	PlayerInputComponent->BindAxis("MoveForward", this, &AFirefighterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFirefighterCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFirefighterCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFirefighterCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFirefighterCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFirefighterCharacter::StopFire);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AFirefighterCharacter::TryInteraction);
}

void AFirefighterCharacter::MoveForward(float Value)
{
	//현재 Controller의 X 방향으로 Value 만큼 이동
	FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFirefighterCharacter::MoveRight(float Value)
{
	//현재 Controller의 Y 방향으로 Value 만큼 이동
	FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFirefighterCharacter::TryInteraction()
{
	if (bIsCarrying || !GetIsReadyToInteraction()) return; //상호작용 불가능 : 업고 있거나 집고 있는 상황

	GamemodeRef->PlayFadeInOutAnimation.Broadcast(0); //PlayerID는 임시로 0
	switch (InteractionType) //상호작용 타입에 따라 구분
	{
	case EFirefighterInteractionType::E_CARRY :
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&](){
			CarryInjuredCharacter(); //FadeIn 중간에 캐릭터를 업음
		}), 0.75f, false); 
		break;
	case EFirefighterInteractionType::E_PICK :
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			InvestigateCauseOfFire(); //FadeIn 중간에 캐릭터를 업음
		}), 0.75f, false);
		break;
	case EFirefighterInteractionType::E_INVESTIGATE :

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
	InjuredCharacterRef->GetRootComponent()->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale); //붙임
	InjuredCharacterRef->GetRootComponent()->SetRelativeLocation({ 20.0f, 30.0f, 30.0f }); //상대 위치와 로테이션 지정
	InjuredCharacterRef->GetRootComponent()->SetRelativeRotation({ 0.0f, 180.0f, 0.0f });
	
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
	if (!IsValid(NewCauseOfFire)) return; //타겟 유효성 체크
	CauseOfFireRef = NewCauseOfFire;
}

void AFirefighterCharacter::SetInjuredCharacterRef(AInjuredCharacter* NewInjuredCharacter)
{
	if (!IsValid(NewInjuredCharacter)) return;
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
