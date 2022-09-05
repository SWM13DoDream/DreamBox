// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/FirefighterCharacter.h"
#include "../public/FirefighterGamemode.h"
#include "../public/FireHose.h"
#include "../public/InjuredCharacter.h"
#include "../public/CauseOfFire.h"
#include "../public/FirefighterGamemode.h"
#include "../public/MissionManager.h"
#include "../public/ScriptManager.h"
#include "Kismet/KismetMathLibrary.h"

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

	ScriptManager = CreateDefaultSubobject<UChildActorComponent>(TEXT("SCRIPT_MANAGER"));
	ScriptManager->SetupAttachment(Super::FollowingCamera);
	ScriptManager->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
	ScriptManager->SetRelativeRotation(FQuat(0.0f, 0.0f, 180.0f, 0.0f));
	ScriptManager->SetRelativeScale3D(FVector(0.4f));

	MissionManager = CreateDefaultSubobject<UChildActorComponent>(TEXT("MISSION_MANAGER"));
	MissionManager->SetupAttachment(Super::VROrigin);
	MissionManager->SetRelativeLocation(FVector(90.0f, -30.0f, 72.5f));
	MissionManager->SetRelativeRotation(FQuat(1980.0f, 90.0f, 2340.0f, 0.0f));
}

// Called when the game starts or when spawned
void AFirefighterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	MissionManagerRef = Cast<AMissionManager>(MissionManager->GetChildActor());
	ScriptManagerRef = Cast<AScriptManager>(ScriptManager->GetChildActor());

	if (GetWorld()) //���Ӹ�� ���۷����� �ʱ�ȭ�ϰ�, �̺�Ʈ�� ���ε�
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
		GamemodeRef->UpdateMissionList.AddDynamic(this, &AFirefighterCharacter::UpdateMissionList);
		GamemodeRef->ShowScriptWithID.AddDynamic(this, &AFirefighterCharacter::ShowScriptWithID);
		GamemodeRef->ShowScriptWithString.AddDynamic(this, &AFirefighterCharacter::ShowScriptWithString);
	}
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
	//���� ����ڸ� ���� ��ȣ�ۿ�
	case EFirefighterInteractionType::E_CARRY :
		GamemodeRef->CrossFadeAnimationEvent.Broadcast(0); //PlayerID�� �ӽ÷� 0
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&](){
			CarryInjuredCharacter(); //FadeIn �߰��� ĳ���͸� ����
		}), 0.75f, false); 
		break;
	
	//������ ���� ��ȣ�ۿ�
	case EFirefighterInteractionType::E_PICK :
		
		break;

	//ȭ�� ���� ���͸� �����ϴ� ��ȣ�ۿ�
	case EFirefighterInteractionType::E_INVESTIGATE :
		GamemodeRef->CrossFadeAnimationEvent.Broadcast(0); //PlayerID�� �ӽ÷� 0
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			InvestigateCauseOfFire(); //FadeIn �߰��� ĳ���͸� ����
			}), 0.75f, false);
		break;

	//�� ��
	default:
		break;
	}
}

void AFirefighterCharacter::Fire()
{
	if (!IsValid(FireHose->GetChildActor())) return; //FireHose ��ȿ�� �˻� 
	Cast<AFireHose>(FireHose->GetChildActor())->ActivateEmitter(); //������ ȣ���� ���̾ư��� �̹��͸� Ȱ��ȭ
}

void AFirefighterCharacter::StopFire()
{
	if (!IsValid(FireHose->GetChildActor())) return; //FireHose ��ȿ�� �˻� 
	Cast<AFireHose>(FireHose->GetChildActor())->DeactivateEmitter();  //������ ȣ���� ���̾ư��� �̹��͸� ��Ȱ��ȭ
}

void AFirefighterCharacter::InvestigateCauseOfFire()
{
	//ȭ�� ���� ���� ��ȿ�� �˻�� ��ȣ�ۿ� ���� ���� üũ
	if (!IsValid(CauseOfFireRef) || !GetIsReadyToInteraction()) return; 
	CauseOfFireRef->Destroy();
}

void AFirefighterCharacter::CarryInjuredCharacter()
{
	//���� ����� ���� ��ȿ�� �˻�� ��ȣ�ۿ� ���� ���� üũ 
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

void AFirefighterCharacter::ResetInteractionState()
{
	SetInjuredCharacterRef(nullptr); //Carry Ÿ�� ĳ���� ����
	SetInteractionType(EFirefighterInteractionType::E_NONE); //��ȣ�ۿ� Ÿ�� None
	SetIsCarrying(false); //���� ���� ������ üũ
	SetIsReadyToInteraction(false); //��ȣ�ۿ��� �غ� �Ǿ����� ������ üũ
}

void AFirefighterCharacter::UpdateMissionList(int32 PlayerID, int32 MissionID, int32 Variable)
{
	if (!IsValid(MissionManagerRef)) return;
	if (Variable == 0) MissionManagerRef->AddNewMission(MissionID);
	else MissionManagerRef->UpdateMission(MissionID, Variable);
}

void AFirefighterCharacter::ShowScriptWithID(int32 PlayerID, int32 ScriptID)
{
	if (!IsValid(ScriptManagerRef)) return;
	ScriptManagerRef->ShowScriptWithID(ScriptID);
}

void AFirefighterCharacter::ShowScriptWithString(int32 PlayerID, FString Script)
{
	if (!IsValid(ScriptManagerRef)) return;
	ScriptManagerRef->ShowScriptWithString(Script);
}