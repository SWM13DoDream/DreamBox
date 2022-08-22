// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/VRCharacter.h"

// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Tags = { "Player" };

	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VR_ORIGIN"));
	VROrigin->SetupAttachment(RootComponent);

	FollowingCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FOLLOWING_CAMERA"));
	FollowingCamera->SetupAttachment(VROrigin);
	FollowingCamera->SetRelativeLocation(FVector(0.0f));
	FollowingCamera->bUsePawnControlRotation = false;
	FollowingCamera->FieldOfView = 58.0f;

	SpectatorRef = CreateDefaultSubobject<USceneComponent>(TEXT("SPECTATOR_REF"));
	SpectatorRef->SetupAttachment(FollowingCamera);

	GenericHMD = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GENERIC_HMD"));
	GenericHMD->SetupAttachment(FollowingCamera);

	HeadCollision = CreateDefaultSubobject<USphereComponent>(TEXT("HEAD_COLLISION"));
	HeadCollision->SetupAttachment(GenericHMD);

	WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WIDGET_INTERACTION"));
	WidgetInteraction->SetupAttachment(FollowingCamera);
	
	bUseControllerRotationYaw = false; //SnapRotate를 위해 컨트롤 Yaw 로테이션 사용을 끔 (오버라이드 방지)
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//입력을 함수와 바인딩
	PlayerInputComponent->BindAxis("SnapTurn", this, &AVRCharacter::SnapTurn);
	PlayerInputComponent->BindAxis("MoveForward", this, &AVRCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVRCharacter::MoveRight);
}

void AVRCharacter::MoveForward(float Value)
{
	//현재 Controller의 X 방향으로 Value 만큼 이동
	FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AVRCharacter::MoveRight(float Value)
{
	//현재 Controller의 Y 방향으로 Value 만큼 이동
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Yellow, "MoveRight");
	FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AVRCharacter::SnapTurn(float Value)
{
	//연속적인 Turn을 방지 (1회만 실시 && 확실하지 않은 입력 시) 
	if (bSnapTurnIsFinished || FMath::Abs(Value) <= 0.5f) return;
	float Direction = (Value < 0.0f ? -1.0f : 1.0f); //좌 &우측 구분
	AddActorWorldRotation({ 0.0f, 45.0f * Direction, 0.0f }, true, nullptr);
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
		ResetSnapTurn();
	}), 0.25f, false); //각 입력의 0.25초 뒤에 새로운 입력이 가능 (연속 입력 방지)

	bSnapTurnIsFinished = true;
}

void AVRCharacter::ResetSnapTurn()
{
	bSnapTurnIsFinished = false;
}