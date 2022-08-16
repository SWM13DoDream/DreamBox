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

	SpectatorRef = CreateDefaultSubobject<USceneComponent>(TEXT("SpectatorRef"));
	SpectatorRef->SetupAttachment(VROrigin);

	FollowingCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FOLLOWING_CAMERA"));
	FollowingCamera->SetupAttachment(VROrigin);
	FollowingCamera->SetRelativeLocation({ 30.0f, 0.0f, 60.0f });
	FollowingCamera->bUsePawnControlRotation = false;
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
	FRotator NewRotation = VROrigin->GetComponentRotation();
	NewRotation.Add(0.0f, -45.0f, 0.0f);
	VROrigin->SetWorldRotation(NewRotation);
	bSnapTurnIsFinished = true; //단일 호출 이후 체크
}

void AVRCharacter::SnapTurnRight()
{
	if (bSnapTurnIsFinished) return; //위와 동일 로직
	FRotator NewRotation = VROrigin->GetComponentRotation();
	NewRotation.Add(0.0f, 45.0f, 0.0f);
	VROrigin->SetWorldRotation(NewRotation);
	bSnapTurnIsFinished = true;
}

void AVRCharacter::ResetSnapTurn()
{
	bSnapTurnIsFinished = false;
}