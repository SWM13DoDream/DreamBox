	// Fill out your copyright notice in the Description page of Project Settings.


#include "./JudgeCharacter.h"

#include "./Chair.h"

// Sets default values
AJudgeCharacter::AJudgeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;

	//WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteraction"));
	//WidgetInteraction->SetupAttachment(GetCapsuleComponent());
	//WidgetInteraction->InteractionDistance = 20000.0f;
	//WidgetInteraction->InteractionSource = EWidgetInteractionSource::CenterScreen;
	//WidgetInteraction->bShowDebug = false;
	//WidgetInteraction->bEnableHitTesting = false;
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
<<<<<<< HEAD
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AJudgeCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AJudgeCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AJudgeCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AJudgeCharacter::LookUp);	
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
	AddControllerYawInput(NewAxisValue);
}

void AJudgeCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

//void AJudgeCharacter::LClickPressed()
//{
//	WidgetInteraction->PressPointerKey(FKey(TEXT("LeftMouseButton")));
//}
//
//void AJudgeCharacter::LClickReleased()
//{
//	WidgetInteraction->ReleasePointerKey(FKey(TEXT("LeftMouseButton")));
//}
=======
}
>>>>>>> 3f33ec6c9923eae5a687803c2b635bece785be65
