// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/RescueGoal.h"
#include "../public/FirefighterCharacter.h"
#include "../public/InjuredCharacter.h"

// Sets default values
ARescueGoal::ARescueGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EventTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("EVENT_TRIGGER"));
	EventTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARescueGoal::BeginPlay()
{
	Super::BeginPlay();
	
	EventTrigger->OnComponentBeginOverlap.AddDynamic(this, &ARescueGoal::TriggerBeginOverlap); //������ �̺�Ʈ

	if (GetWorld()) //���Ӹ�� ���۷��� ����
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
	}
}

// Called every frame
void ARescueGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ARescueGoal::TriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || !IsValid(GamemodeRef)) return; //ĳ���Ϳ� ���Ӹ�� ��ȿ�� �˻�

	FirefighterCharacterRef = Cast<AFirefighterCharacter>(OtherActor); //���۷��� ����
	if (!FirefighterCharacterRef->GetIsCarrying()) return; //ĳ���͸� �ҷ��� �� ���ų� ���� �ִ� ĳ���Ͱ� ���ٸ� ��ȯ

	AInjuredCharacter* injuredCharacter = FirefighterCharacterRef->GetInjuredCharacterRef(); //���۷��� ����
	if (!IsValid(injuredCharacter)) return; //������� ĳ���Ͱ� ��ȿ���� �ʰų� �̼�ID�� �ٸ��ٸ� ��ȯ
	if (MissionID != 0 && MissionID != injuredCharacter->GetMissionID()) return; //ID�� 0? : ����

	GamemodeRef->PlayFadeInOutAnimation.Broadcast(0);  //FadeIn �ִϸ��̼� 
	GamemodeRef->UpdateMissionListComponent.Broadcast(0, injuredCharacter->GetMissionID(), 1); //�̼� ������Ʈ 
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&](){ //FadeIn �߰��� ĳ���͸� ������
		FirefighterCharacterRef->PutInjuredCharacter();
		CurrentRescueCount += 1;
		if(TargetRescueCount == CurrentRescueCount) Destroy();
	}), 0.75f, false);
}