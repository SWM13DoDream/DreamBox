// Fill out your copyright notice in the Description page of Project Settings.


#include "./NpcCharacter.h"

// Sets default values
ANpcCharacter::ANpcCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ScriptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chair"));


	ScriptWidget->SetDrawSize(FVector2D(700.0f, 300.0f));
	ScriptWidget->SetupAttachment(GetCapsuleComponent());

	StaticMesh->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANpcCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANpcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

