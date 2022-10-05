// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/NpcCharacter.h"
#include "../public/SScriptStruct.h"
#include "../../common/public/PersistentLevelBase.h"
#include "../public/JudgeGameMode.h"
#include "Engine/DataTable.h"
#include "Components/WidgetComponent.h"

// Sets default values
ANpcCharacter::ANpcCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ScriptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));

	ScriptWidget->SetDrawSize(FVector2D(300.0f, 250.0f));
	ScriptWidget->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetWorld())
	{
		GamemodeRef = Cast<AJudgeGameMode>(GetWorld()->GetAuthGameMode());
		LevelScriptRef = Cast<APersistentLevelBase>(GetWorld()->GetLevelScriptActor());
		if (IsValid(LevelScriptRef))
		{
			LevelScriptRef->PostLoadingDelegate.AddDynamic(this, &ANpcCharacter::PostLoadingEvent);
		}
	}
}

void ANpcCharacter::PostLoadingEvent()
{
	AddArray(FirstScriptDT, FirstScript, FirstDelay);
	AddArray(SecondScriptDT, SecondScript, SecondDelay);
	AddArray(ThirdScriptDT, ThirdScript, ThirdDelay);
	AddArray(FourthScriptDT, FourthScript, FourthDelay);
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

void ANpcCharacter::AddArray(UDataTable* Table, TArray<FString>& ScriptArray, TArray<float>& DelayArray)
{
	if (Table != NULL) {
		TArray<FScriptStructure*> Array;
		Table->GetAllRows<FScriptStructure>(TEXT("GetAllRows"), Array);

		for (int i = 0; i < Array.Num(); ++i)
		{
			if (Array[i]->Script.Equals("")) break;
			ScriptArray.Add(*Array[i]->Script);
			DelayArray.Add(Array[i]->TimeLength);
		}
	}
}

