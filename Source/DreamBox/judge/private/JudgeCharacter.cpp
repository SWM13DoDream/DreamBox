	// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/JudgeCharacter.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AJudgeCharacter::AJudgeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 캐릭터가 시작될 때 Player0으로 시작되게 만듬
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	// 캐릭터의 이동 속도를 250으로 변경
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

	// 마우스의 이동을 바인딩 [ 마우스 ]
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AJudgeCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AJudgeCharacter::AddControllerPitchInput);
}