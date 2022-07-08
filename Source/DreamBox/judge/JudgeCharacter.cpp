// Fill out your copyright notice in the Description page of Project Settings.


#include "./JudgeCharacter.h"

// Sets default values
AJudgeCharacter::AJudgeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(RootComponent);
	Camera->SetRelativeLocation(FVector(0, 0, 40));
	
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
	WidgetInteraction->AttachTo(GetCapsuleComponent());
	WidgetInteraction->InteractionDistance = 20000.0f;
	WidgetInteraction->InteractionSource = EWidgetInteractionSource::CenterScreen;
	WidgetInteraction->bShowDebug = false;
	WidgetInteraction->bEnableHitTesting = false;
}

// Called when the game starts or when spawned
void AJudgeCharacter::BeginPlay()
{
	Super::BeginPlay();
}
/*aaa*/
// Called every frame
void AJudgeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJudgeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AJudgeCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AJudgeCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AJudgeCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AJudgeCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("LClick"), EInputEvent::IE_Pressed, this, &AJudgeCharacter::LClickPressed);
	PlayerInputComponent->BindAction(TEXT("LClick"), EInputEvent::IE_Released, this, &AJudgeCharacter::LClickReleased);
}

void AJudgeCharacter::MoveForward(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AJudgeCharacter::MoveRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}

void AJudgeCharacter::Turn(float NewAxisValue)
{
	AddActorLocalRotation(FRotator(0, NewAxisValue, 0));
}

void AJudgeCharacter::LookUp(float NewAxisValue)
{
	float temp = Camera->GetRelativeRotation().Pitch + NewAxisValue;

	if (temp < 65 && temp > -65)
	{
		Camera->AddLocalRotation(FRotator(NewAxisValue * -1, 0, 0));
	}
}

void AJudgeCharacter::LClickPressed()
{
	WidgetInteraction->PressPointerKey(FKey(TEXT("LeftMouseButton")));
}

void AJudgeCharacter::LClickReleased()
{
	WidgetInteraction->ReleasePointerKey(FKey(TEXT("LeftMouseButton")));
}
