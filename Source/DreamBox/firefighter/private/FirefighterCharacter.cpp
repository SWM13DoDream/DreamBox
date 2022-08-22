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
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFirefighterCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFirefighterCharacter::StopFire);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AFirefighterCharacter::TryInteraction);
}

void AFirefighterCharacter::TryInteraction()
{
	if (bIsCarrying || !GetIsReadyToInteraction()) return; //��ȣ�ۿ� �Ұ��� : ���� �ְų� ���� �ִ� ��Ȳ

	switch (InteractionType) //��ȣ�ۿ� Ÿ�Կ� ���� ����
	{
	case EFirefighterInteractionType::E_CARRY :
		GamemodeRef->PlayFadeInOutAnimation.Broadcast(0); //PlayerID�� �ӽ÷� 0
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&](){
			CarryInjuredCharacter(); //FadeIn �߰��� ĳ���͸� ����
		}), 0.75f, false); 
		break;
	case EFirefighterInteractionType::E_PICK :
		
		break;
	case EFirefighterInteractionType::E_INVESTIGATE :
		GamemodeRef->PlayFadeInOutAnimation.Broadcast(0); //PlayerID�� �ӽ÷� 0
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			InvestigateCauseOfFire(); //FadeIn �߰��� ĳ���͸� ����
			}), 0.75f, false);
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
	InjuredCharacterRef->GetRootComponent()->AttachToComponent(RescueSocket, FAttachmentTransformRules::SnapToTargetNotIncludingScale); //����
	InjuredCharacterRef->GetRootComponent()->SetRelativeLocation({ 20.0f, 40.0f, 30.0f }); //��� ��ġ�� �����̼� ����
	InjuredCharacterRef->GetRootComponent()->SetRelativeRotation({ 0.0f, 0.0f, 0.0f });
	
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
	SetInjuredCharacterRef(nullptr); //Carry Ÿ�� ĳ���� ����
	SetInteractionType(EFirefighterInteractionType::E_NONE); //��ȣ�ۿ� Ÿ�� None
	SetIsCarrying(false); //���� ���� ������ üũ
	SetIsReadyToInteraction(false); //��ȣ�ۿ��� �غ� �Ǿ����� ������ üũ
}
