// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/InjuredCharacter.h"
#include "../public/FirefighterCharacter.h"
#include "../public/FirefighterGamemode.h"
#include "Components/WidgetComponent.h"

// Sets default values
AInjuredCharacter::AInjuredCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("INTERACTION_TRIGGER"));
	InteractionTrigger->SetupAttachment(RootComponent);
	InteractionTrigger->SetRelativeLocation(FVector(0.0f));
	InteractionTrigger->SetWorldScale3D(FVector(5.0f));

	RescueGuideMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RESCUE_GUIDE_MESH"));
	RescueGuideMesh->SetupAttachment(RootComponent);
	RescueGuideMesh->SetRelativeLocation(FVector(0.0f));
	RescueGuideMesh->SetVisibility(false);

	InfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INFO_WIDGET"));
	InfoWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInjuredCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionTrigger->OnComponentBeginOverlap.AddDynamic(this, &AInjuredCharacter::InteractionTriggerBeginOverlap);
	InteractionTrigger->OnComponentEndOverlap.AddDynamic(this, &AInjuredCharacter::InteractionTriggerEndOverlap);
	GetMovementComponent()->Deactivate();

	if (GetWorld()) //Gamemode ���۷����� �ʱ�ȭ�ϰ� �̼� ������Ʈ�� ���� �̺�Ʈ�� ���ε�
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
		GamemodeRef->UpdateMissionList.AddDynamic(this, &AInjuredCharacter::TryActivateMissionActor);
	}
}

// Called every frame
void AInjuredCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInjuredCharacter::InteractionTriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || bIsBeingRescued || !bIsActivated) return; //�÷��̾� ��ȿ�� �˻�� ���ͷ��� ���� ���� �˻�

	AFirefighterCharacter* playerCharacter = Cast<AFirefighterCharacter>(OtherActor);
	if (playerCharacter->GetIsCarrying()) //�÷��̾ �̹� ���� �ִٸ� �޽����� ����ϰ� ��ȯ
	{
		GamemodeRef->ShowScriptWithString.Broadcast(0, FString("�� �� �̻� ���� �� �����ϴ�."));
		return; 
	}
	playerCharacter->SetInteractionType(EFirefighterInteractionType::E_CARRY); //ĳ������ ������ ��ȣ�ۿ� Ÿ�� ����
	playerCharacter->SetIsReadyToInteraction(true); //��ȣ�ۿ� ���������� üũ
	playerCharacter->SetInjuredCharacterRef(this); //���� ����� (this)�� ĳ���Ϳ��� ����
}

void AInjuredCharacter::InteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || bIsBeingRescued || !bIsActivated) return; //��ȿ�� �˻�
	AFirefighterCharacter* playerCharacter = Cast<AFirefighterCharacter>(OtherActor); //���۷��� ����
	playerCharacter->SetInteractionType(EFirefighterInteractionType::E_NONE); //��ȣ�ۿ� None���� �ѹ�
	playerCharacter->SetIsReadyToInteraction(false); //��ȣ�ۿ� �Ұ���
}

void AInjuredCharacter::SetCharacterCollisionState(bool NewState)
{
	if (NewState) GetCapsuleComponent()->SetCollisionProfileName(FName("Pawn")); //���̶�� ����Ʈ �ݸ������� ����
	else GetCapsuleComponent()->SetCollisionProfileName(FName("OverlapAll")); //�����̶�� �ݸ��� ����
}

void AInjuredCharacter::SetIsBeingRescued(bool NewState)
{
	if (NewState) //���� �����Ǵ� ���¶��?
	{
		RescueGuideMesh->SetVisibility(false); // ���� ���̵� ���� �޽ÿ�
		InfoWidget->SetVisibility(false); //���� ������ ����
	}
	bIsBeingRescued = NewState; 
}

void AInjuredCharacter::TryActivateMissionActor(int32 TargetPlayerId, int32 NewMissionId, int32 Variable)
{
	if (MissionID != NewMissionId || Variable) return;  //���ŵǴ� �̼��̰ų� ���� �� NPC�� �̼��� �ٸ��ٸ� ��ȯ
	bIsActivated = true; //�Ҵ�� ID�� �´� �̼��� �߰��Ǿ��ٸ�? ���� Interaction�� �����ϵ��� Activate
	RescueGuideMesh->SetVisibility(true); //���̵� �޽õ� Visible�ϰ� ó��
}
