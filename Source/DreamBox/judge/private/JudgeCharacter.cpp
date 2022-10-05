	// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/JudgeCharacter.h"
#include "../../common/public/PersistentLevelBase.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AJudgeCharacter::AJudgeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ScriptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SCRIPT"));
	ScriptWidget->SetupAttachment(FollowingCamera);
	ScriptWidget->SetRelativeLocation({ 60.0f, 0.0f, -25.0f });
	ScriptWidget->SetRelativeScale3D({ 1.0f, 0.07f, 0.07f });
	ScriptWidget->SetDrawSize({ 800.0f, 150.0f });
	ScriptWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AJudgeCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetLevelScriptRef()))
	{
		GetLevelScriptRef()->PreLoadingEndDelegate.AddDynamic(this, &AJudgeCharacter::PreLoadingEnd);
		GetLevelScriptRef()->PostLoadingDelegate.AddDynamic(this, &AJudgeCharacter::PostLoadingEvent);
	}
}

// Called every frame
void AJudgeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJudgeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJudgeCharacter::PreLoadingEnd()
{
	PlayLevelSequence(EPlayerLevelSequenceType::E_CrossFade);

	if (IsValid(GetLevelScriptRef()))
	{
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			GetLevelScriptRef()->PostLoadingDelegate.Broadcast();
		}), 0.75f, false);
	}
}

void AJudgeCharacter::PostLoadingEvent()
{
	ScriptWidget->SetVisibility(true);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}