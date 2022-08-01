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
	//if(IsValid(GamemodeRef)) GamemodeRef->UpdateMissionList() //BP �ڵ忡�� ���� ����@@@
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

	//�Է��� �Լ��� ���ε�
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
	//���� Controller�� X �������� Value ��ŭ �̵�
	FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFirefighterCharacter::MoveRight(float Value)
{
	//���� Controller�� Y �������� Value ��ŭ �̵�
	FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFirefighterCharacter::TryInteraction()
{
	if (bIsCarrying || !GetIsReadyToInteraction()) return; //��ȣ�ۿ� �Ұ��� : ���� �ְų� ���� �ִ� ��Ȳ

	GamemodeRef->PlayFadeInOutAnimation.Broadcast(0); //PlayerID�� �ӽ÷� 0
	switch (InteractionType) //��ȣ�ۿ� Ÿ�Կ� ���� ����
	{
	case EFirefighterInteractionType::E_CARRY :
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&](){
			CarryInjuredCharacter(); //FadeIn �߰��� ĳ���͸� ����
		}), 0.75f, false); 
		break;
	case EFirefighterInteractionType::E_PICK :
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			InvestigateCauseOfFire(); //FadeIn �߰��� ĳ���͸� ����
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
	Cast<AFireHose>(FireHose->GetChildActor())->ActivateEmitter(); //������ ȣ���� ���̾ư��� �̹��͸� Ȱ��ȭ
}

void AFirefighterCharacter::StopFire()
{
	if (!IsValid(FireHose->GetChildActor())) return;
	Cast<AFireHose>(FireHose->GetChildActor())->DeactivateEmitter();  //������ ȣ���� ���̾ư��� �̹��͸� ��Ȱ��ȭ
}

void AFirefighterCharacter::InvestigateCauseOfFire()
{
	if (!IsValid(CauseOfFireRef) || !GetIsReadyToInteraction()) return; 
	CauseOfFireRef->Destroy();
}

void AFirefighterCharacter::CarryInjuredCharacter()
{
	if (!IsValid(InjuredCharacterRef) && !InjuredCharacterRef->GetIsBeingRescued()) return; //Ÿ���� ��ȿ���� �ʰų� �̹� �����ǰ� �ִ� ĳ���Ͷ��
	if (bIsCarrying || !bIsReadyToInteraction) return; //�̹� ���� �ְų� ��ȣ�ۿ� �� �غ� ���� �ʾҴٸ�

	InjuredCharacterRef->SetIsBeingRescued(true); //Ÿ�� ĳ���Ͱ� ������(������)�̶�� üũ
	InjuredCharacterRef->SetCharacterCollisionState(false); //�ݸ��� ����
	InjuredCharacterRef->GetRootComponent()->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale); //����
	InjuredCharacterRef->GetRootComponent()->SetRelativeLocation({ 20.0f, 30.0f, 30.0f }); //��� ��ġ�� �����̼� ����
	InjuredCharacterRef->GetRootComponent()->SetRelativeRotation({ 0.0f, 180.0f, 0.0f });
	
	SetIsCarrying(true); //�����ִٰ� üũ
	SetIsReadyToInteraction(false); //��ȣ�ۿ� �Ұ���
}

void AFirefighterCharacter::PutInjuredCharacter()
{
	if (!IsValid(InjuredCharacterRef)) return; // Ÿ�� ��ȿ�� üũ
	InjuredCharacterRef->Destroy(); //Ÿ�� ĳ���� �Ҹ�
	ResetInteractionState(); //���ͷ��� �������� �ʱ�ȭ 
}

void AFirefighterCharacter::SetCauseOfFireRef(ACauseOfFire* NewCauseOfFire)
{
	if (!IsValid(NewCauseOfFire)) return; //Ÿ�� ��ȿ�� üũ
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
	SetInjuredCharacterRef(nullptr); //Carry Ÿ�� ĳ���� ����
	SetInteractionType(EFirefighterInteractionType::E_NONE); //��ȣ�ۿ� Ÿ�� None
	SetIsCarrying(false); //���� ���� ������ üũ
	SetIsReadyToInteraction(false); //��ȣ�ۿ��� �غ� �Ǿ����� ������ üũ
}
