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
	
	bUseControllerRotationYaw = false; //SnapRotate�� ���� ��Ʈ�� Yaw �����̼� ����� �� (�������̵� ����)
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
	//���� Controller�� X �������� Value ��ŭ �̵�
	FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AVRCharacter::MoveRight(float Value)
{
	//���� Controller�� Y �������� Value ��ŭ �̵�
	FVector Direction = FRotationMatrix(FollowingCamera->GetComponentRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AVRCharacter::SnapTurnLeft()
{
	if (bSnapTurnIsFinished) return; //�� ������ ��, ���� ȣ���� ���� �ʵ��� ����
	AddActorWorldRotation({ 0.0f, -45.0f, 0.0f }, false, nullptr, ETeleportType::TeleportPhysics);
	bSnapTurnIsFinished = true; //���� ȣ�� ���� üũ
}

void AVRCharacter::SnapTurnRight()
{
	if (bSnapTurnIsFinished) return; //���� ���� ����
	AddActorWorldRotation({ 0.0f, 45.0f, 0.0f }, false, nullptr, ETeleportType::TeleportPhysics);
	bSnapTurnIsFinished = true;
}

void AVRCharacter::ResetSnapTurn()
{
	bSnapTurnIsFinished = false;

}