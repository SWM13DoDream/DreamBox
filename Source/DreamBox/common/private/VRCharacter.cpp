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

void AVRCharacter::MoveForward(float Value)
{
	//현재 Controller의 X 방향으로 Value 만큼 이동
	FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AVRCharacter::MoveRight(float Value)
{
	//현재 Controller의 Y 방향으로 Value 만큼 이동
	FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AVRCharacter::SnapTurnLeft()
{
	if (bSnapTurnIsFinished) return; //꾹 눌렀을 때, 연속 호출이 되지 않도록 방지
	AddActorWorldRotation({ 0.0f, -45.0f, 0.0f }, false, nullptr, ETeleportType::TeleportPhysics);
	bSnapTurnIsFinished = true; //단일 호출 이후 체크
}

void AVRCharacter::SnapTurnRight()
{
	if (bSnapTurnIsFinished) return; //위와 동일 로직
	AddActorWorldRotation({ 0.0f, 45.0f, 0.0f }, false, nullptr, ETeleportType::TeleportPhysics);
	bSnapTurnIsFinished = true;
}

void AVRCharacter::ResetSnapTurn()
{
	bSnapTurnIsFinished = false;

}