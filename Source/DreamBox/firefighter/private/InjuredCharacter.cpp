// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/InjuredCharacter.h"
#include "../public/FirefighterCharacter.h"

// Sets default values
AInjuredCharacter::AInjuredCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionTextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("INTERACTION_TEXT"));
	InteractionTextRender->SetupAttachment(RootComponent);
	InteractionTextRender->SetRelativeLocation({0.0f, 0.0f, 15.0f});
	InteractionTextRender->SetVisibility(false); //�ʱ� Visibility�� false

	InteractionTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("INTERACTION_TRIGGER"));
	InteractionTrigger->SetupAttachment(RootComponent);
	InteractionTrigger->SetWorldScale3D(FVector(5.0f));
}

// Called when the game starts or when spawned
void AInjuredCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionTrigger->OnComponentBeginOverlap.AddDynamic(this, &AInjuredCharacter::InteractionTriggerBeginOverlap);
	InteractionTrigger->OnComponentEndOverlap.AddDynamic(this, &AInjuredCharacter::InteractionTriggerEndOverlap);
	
	if (GetWorld()) //Gamemode ���۷����� �ʱ�ȭ
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
	}
}

// Called every frame
void AInjuredCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInjuredCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AInjuredCharacter::InteractionTriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || bIsBeingRescued || bIsRescued) return; //�÷��̾� ��ȿ�� �˻�� ���ͷ��� ���� ���� �˻�

	AFirefighterCharacter* playerCharacter = Cast<AFirefighterCharacter>(OtherActor);
	if (playerCharacter->GetIsCarrying()) //�÷��̾ �̹� ���� �ִٸ� �޽����� ����ϰ� ��ȯ
	{
		//** Message Delegate : �� �� �̻� ���� �� �����ϴ�!
		return; 
	}
	InteractionTextRender->SetVisibility(true); //�ȳ� �ؽ�Ʈ�� ���� 
	playerCharacter->SetInteractionType(EFirefighterInteractionType::E_CARRY); //ĳ������ ������ ��ȣ�ۿ� Ÿ�� ����
	playerCharacter->SetIsReadyToInteraction(true); //��ȣ�ۿ� ���������� üũ
	playerCharacter->SetInjuredCharacterRef(this); //���� ����� (this)�� ĳ���Ϳ��� ����
}

void AInjuredCharacter::InteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || bIsBeingRescued || bIsRescued) return; //��ȿ�� �˻�
	AFirefighterCharacter* playerCharacter = Cast<AFirefighterCharacter>(OtherActor); //���۷��� ����
	InteractionTextRender->SetVisibility(false); //�ȳ� �ؽ�Ʈ ����
	playerCharacter->SetInteractionType(EFirefighterInteractionType::E_NONE); //��ȣ�ۿ� None���� �ѹ�
	playerCharacter->SetIsReadyToInteraction(false); //��ȣ�ۿ� �Ұ���
}

void AInjuredCharacter::SetCharacterCollisionState(bool NewState)
{
	if (NewState) GetCapsuleComponent()->SetCollisionProfileName(FName("Pawn")); //���̶�� ����Ʈ �ݸ������� ����
	else GetCapsuleComponent()->SetCollisionProfileName(FName("NoCollision")); //�����̶�� �ݸ��� ����
}

void AInjuredCharacter::SetIsBeingRescued(bool NewState)
{
	if (NewState) InteractionTextRender->SetVisibility(false); //�����߿��� TextRender�� ����
	bIsBeingRescued = NewState; 
}