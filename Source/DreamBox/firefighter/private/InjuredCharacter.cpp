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

	if (GetWorld()) //Gamemode 레퍼런스를 초기화하고 미션 업데이트를 위한 이벤트를 바인딩
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
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || bIsBeingRescued || !bIsActivated) return; //플레이어 유효성 검사와 인터렉션 가능 조건 검사

	AFirefighterCharacter* playerCharacter = Cast<AFirefighterCharacter>(OtherActor);
	if (playerCharacter->GetIsCarrying()) //플레이어가 이미 업고 있다면 메시지를 출력하고 반환
	{
		GamemodeRef->ShowScriptWithString.Broadcast(0, FString("두 명 이상 업을 수 없습니다."));
		return; 
	}
	playerCharacter->SetInteractionType(EFirefighterInteractionType::E_CARRY); //캐릭터의 가능한 상호작용 타입 지정
	playerCharacter->SetIsReadyToInteraction(true); //상호작용 가능함으로 체크
	playerCharacter->SetInjuredCharacterRef(this); //업을 대상인 (this)를 캐릭터에게 전달
}

void AInjuredCharacter::InteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || bIsBeingRescued || !bIsActivated) return; //유효성 검사
	AFirefighterCharacter* playerCharacter = Cast<AFirefighterCharacter>(OtherActor); //레퍼런스 얻음
	playerCharacter->SetInteractionType(EFirefighterInteractionType::E_NONE); //상호작용 None으로 롤백
	playerCharacter->SetIsReadyToInteraction(false); //상호작용 불가능
}

void AInjuredCharacter::SetCharacterCollisionState(bool NewState)
{
	if (NewState) GetCapsuleComponent()->SetCollisionProfileName(FName("Pawn")); //참이라면 디폴트 콜리전으로 지정
	else GetCapsuleComponent()->SetCollisionProfileName(FName("OverlapAll")); //거짓이라면 콜리전 제거
}

void AInjuredCharacter::SetIsBeingRescued(bool NewState)
{
	if (NewState) //만약 구조되는 상태라면?
	{
		RescueGuideMesh->SetVisibility(false); // 구조 가이드 원형 메시와
		InfoWidget->SetVisibility(false); //정보 위젯을 숨김
	}
	bIsBeingRescued = NewState; 
}

void AInjuredCharacter::TryActivateMissionActor(int32 TargetPlayerId, int32 NewMissionId, int32 Variable)
{
	if (MissionID != NewMissionId || Variable) return;  //제거되는 미션이거나 현재 이 NPC와 미션이 다르다면 반환
	bIsActivated = true; //할당된 ID에 맞는 미션이 추가되었다면? 구조 Interaction이 가능하도록 Activate
	RescueGuideMesh->SetVisibility(true); //가이드 메시도 Visible하게 처리
}
