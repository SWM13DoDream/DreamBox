	// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/JudgeCharacter.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AJudgeCharacter::AJudgeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// ĳ���Ͱ� ���۵� �� Player0���� ���۵ǰ� ����
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	// ĳ������ �̵� �ӵ��� 250���� ����
	GetCharacterMovement()->MaxWalkSpeed = 250.0f;
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

	// ���콺�� �̵��� ���ε� [ ���콺 ]
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AJudgeCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AJudgeCharacter::AddControllerPitchInput);
}