// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/VRCharacter.h"
#include "../public/PersistentLevelBase.h"
#include "TimerManager.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "SocketSubsystem.h"
#include "Components/WidgetInteractionComponent.h"

/*
 - Name        : AVRCharacter
 - Description : VRImmersiveHands ���� ����� Base ĳ���� Ŭ����
				 ������ ĳ���͸� �� Ŭ������ ���
 - Date        : 2022/09/28 LJH
*/

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
	WidgetInteraction->ComponentTags = { "Widget" };

	bUseControllerRotationYaw = false; //SnapRotate�� ���� ��Ʈ�� Yaw �����̼� ����� �� (�������̵� ����)
}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();	

	PlayerControllerID = UGameplayStatics::GetPlayerControllerID(Cast<APlayerController>(Controller));

	InitLevelScriptRef();
	InitGameModeRef();
	InitLevelSequence();
	
	SetCanJump(true);
}


// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//�Է��� �Լ��� ���ε�
	PlayerInputComponent->BindAxis("SnapTurn", this, &AVRCharacter::SnapTurn);
	PlayerInputComponent->BindAxis("MoveForward", this, &AVRCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVRCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Interaction", IE_Released, this, &ACharacter::StopJumping);
}

void AVRCharacter::OnRPCSetupContent_Implementation(int32 PlayerID, FContentStartInfo StartInfo)
{
	UE_LOG(LogTemp, Warning, TEXT("SIBAL"));
	if (HasAuthority())
	{
		OnRPCInitPlayerTransform(FTransform(StartInfo.StartRotation, StartInfo.StartLocation, FVector(1.0f)));
	}
	else
	{
		MakeRPCInitPlayerTransform(FTransform(StartInfo.StartRotation, StartInfo.StartLocation, FVector(1.0f)));
	}
}

void AVRCharacter::OnRPCStartContent_Implementation(int32 PlayerID)
{
	UE_LOG(LogTemp, Warnings, TEXT("OnRPCStartContent"));
}

void AVRCharacter::MakeRPCInitPlayerTransform_Implementation(FTransform InitialTransform)
{
	OnRPCInitPlayerTransform(InitialTransform);
}

void AVRCharacter::OnRPCInitPlayerTransform_Implementation(FTransform InitialTransform)
{
	SetActorLocation(InitialTransform.GetLocation(), false, nullptr, ETeleportType::TeleportPhysics);
	SetActorRotation(InitialTransform.GetRotation(), ETeleportType::TeleportPhysics);
}

void AVRCharacter::InitLevelSequence()
{
	ALevelSequenceActor* OutActor = nullptr;

	for (ULevelSequence* levelSequenceRef : LevelSequenceList)
	{
		if (IsValid(levelSequenceRef))
		{
			LevelSequencePlayerList.Add(ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), levelSequenceRef
				, FMovieSceneSequencePlaybackSettings(), OutActor));
		}
	}
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

void AVRCharacter::SnapTurn(float Value)
{
	//�������� Turn�� ���� (1ȸ�� �ǽ� && Ȯ������ ���� �Է� ��) 
	if (bSnapTurnIsFinished || FMath::Abs(Value) <= 0.5f) return;

	float Direction = (Value < 0.0f ? -1.0f : 1.0f); //�� & ���� ����
	AddActorWorldRotation({ 0.0f, 45.0f * Direction, 0.0f }, true, nullptr); //�����̼��� 45�� ����

	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
		ResetSnapTurnControllerInput();
	}), 0.15f, false); //�� �Է��� 0.15�� �ڿ� ���ο� �Է��� ���� (���� �Է� ����)

	bSnapTurnIsFinished = true;
}

void AVRCharacter::ResetSnapTurnControllerInput()
{
	bSnapTurnIsFinished = false; //�ٽ� SnapTurn�� �� �� �ֵ��� ����
}

void AVRCharacter::PlayLevelInitSequence_Implementation()
{
	PlayLevelSequence(EPlayerLevelSequenceType::E_FadeIn);
}

float AVRCharacter::PlayLevelSequence(EPlayerLevelSequenceType TargetSequenceType)
{
	if (LevelSequencePlayerList.IsValidIndex((int32)(TargetSequenceType)))
	{
		if (IsValid(LevelSequencePlayerList[(int32)(TargetSequenceType)]))
		{
			LevelSequencePlayerList[(int32)(TargetSequenceType)]->Play();

			if (LevelSequenceLengthList.IsValidIndex((int32)(TargetSequenceType)))
			{
				GetCharacterMovement()->Deactivate();
				GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
					GetCharacterMovement()->Activate();
				}), LevelSequenceLengthList[(int32)(TargetSequenceType)], false);

				return LevelSequenceLengthList[(int32)(TargetSequenceType)];
			}
		}
	}	
	return 0.0f;
}

void AVRCharacter::SetCanJump(bool NewState)
{
	GetCharacterMovement()->SetJumpAllowed(NewState);
}

void AVRCharacter::InitGameModeRef()
{
	if (GetWorld())
	{
		GamemodeRef = GetWorld()->GetAuthGameMode<ADreamBoxGameModeBase>();
	}
}

void AVRCharacter::InitLevelScriptRef()
{
	if (GetWorld())
	{
		LevelScriptRef = Cast<APersistentLevelBase>(GetWorld()->GetLevelScriptActor());
	}
}


FString AVRCharacter::GetCurrentIpAddress()
{
	FString IpAddr("NONE");
	bool canBind = false;
	TSharedRef<class FInternetAddr> LocalIp = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, canBind);
	if (LocalIp->IsValid())
	{
		IpAddr = LocalIp->ToString(false);
	}
	return IpAddr;
}
