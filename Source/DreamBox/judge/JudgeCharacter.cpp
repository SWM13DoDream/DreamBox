	// Fill out your copyright notice in the Description page of Project Settings.


#include "./JudgeCharacter.h"

// Sets default values
AJudgeCharacter::AJudgeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	
	ScriptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("ScriptWidget"));
	ScriptWidget->SetupAttachment(RootComponent);
	ScriptWidget->SetDrawSize(FVector2D(1920.f, 400.f));
	ScriptWidget->SetWorldRotation(FRotator(15.f, 180.f, 0.f));
	ScriptWidget->SetRelativeLocation(FVector(130.0f, 13.0f, -50.0f));
	ScriptWidget->SetWorldScale3D(FVector(1.0f, 0.07f, 0.07f));
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

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AJudgeCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AJudgeCharacter::AddControllerPitchInput);
}

void AJudgeCharacter::MoveForward(float NewAxisValue)
{
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AJudgeCharacter::MoveRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}