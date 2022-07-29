// Fill out your copyright notice in the Description page of Project Settings.

#include "../public/InjuredCharacter.h"
#include "../public/FirefighterCharacter.h"

// Sets default values
AInjuredCharacter::AInjuredCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	CapsuleComponent->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Mesh->SetupAttachment(RootComponent);

	InteractionTextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("INTERACTION_TEXT"));
	InteractionTextRender->SetupAttachment(RootComponent);
	InteractionTextRender->SetRelativeLocation({0.0f, 0.0f, 15.0f});
	InteractionTextRender->SetVisibility(false); //초기 Visibility는 false

	InteractionTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("INTERACTION_TRIGGER"));
	InteractionTrigger->SetupAttachment(RootComponent);
	InteractionTrigger->SetWorldScale3D(FVector(5.0f));

	RescueGuideMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RESCUE_GUIDE_MESH"));
	RescueGuideMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInjuredCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionTrigger->OnComponentBeginOverlap.AddDynamic(this, &AInjuredCharacter::InteractionTriggerBeginOverlap);
	InteractionTrigger->OnComponentEndOverlap.AddDynamic(this, &AInjuredCharacter::InteractionTriggerEndOverlap);
	
	if (GetWorld()) //Gamemode 레퍼런스를 초기화
	{
		GamemodeRef = Cast<AFirefighterGamemode>(GetWorld()->GetAuthGameMode());
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
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlap"));

	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || bIsBeingRescued || bIsRescued) return; //플레이어 유효성 검사와 인터렉션 가능 조건 검사

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Start!"));

	AFirefighterCharacter* playerCharacter = Cast<AFirefighterCharacter>(OtherActor);
	if (playerCharacter->GetIsCarrying()) //플레이어가 이미 업고 있다면 메시지를 출력하고 반환
	{
		//** Message Delegate : 두 명 이상 업을 수 없습니다!
		return; 
	}
	InteractionTextRender->SetVisibility(true); //안내 텍스트를 보임 
	playerCharacter->SetInteractionType(EFirefighterInteractionType::E_CARRY); //캐릭터의 가능한 상호작용 타입 지정
	playerCharacter->SetIsReadyToInteraction(true); //상호작용 가능함으로 체크
	playerCharacter->SetInjuredCharacterRef(this); //업을 대상인 (this)를 캐릭터에게 전달
}

void AInjuredCharacter::InteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player") || bIsBeingRescued || bIsRescued) return; //유효성 검사
	AFirefighterCharacter* playerCharacter = Cast<AFirefighterCharacter>(OtherActor); //레퍼런스 얻음
	InteractionTextRender->SetVisibility(false); //안내 텍스트 숨김
	playerCharacter->SetInteractionType(EFirefighterInteractionType::E_NONE); //상호작용 None으로 롤백
	playerCharacter->SetIsReadyToInteraction(false); //상호작용 불가능
}

void AInjuredCharacter::SetCharacterCollisionState(bool NewState)
{
	if (NewState) CapsuleComponent->SetCollisionProfileName(FName("Pawn")); //참이라면 디폴트 콜리전으로 지정
	else CapsuleComponent->SetCollisionProfileName(FName("OverlapAll")); //거짓이라면 콜리전 제거
}

void AInjuredCharacter::SetIsBeingRescued(bool NewState)
{
	if (NewState)
	{
		InteractionTextRender->SetVisibility(false); //구조중에는 TextRender를 숨김
		RescueGuideMesh->SetWorldScale3D(FVector(0.0f));
	}
	bIsBeingRescued = NewState; 
}