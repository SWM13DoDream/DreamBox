// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: ANpcCharacter
- Description	: 검사 / 변호사 / 피고인을 위한 Character
- Date			: 2022-09-24 LJH
*/

#pragma once

#include "../../common/public/DreamBox.h"
#include "NpcCharacter.generated.h"

UCLASS()
class DREAMBOX_API ANpcCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpcCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void BeginPlayAfterLoading();

	// DataTable를 통해 Script와 Delay를 각각 배열에 집어넣는 함수
	UFUNCTION()
		void AddArray(class UDataTable* Table, TArray<FString>& ScriptArray, TArray<float>& DelayArray);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
		class UWidgetComponent* ScriptWidget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		class UDataTable* FirstScriptDT;
	UPROPERTY(BlueprintReadWrite, Category = "Script")
		TArray<FString> FirstScript;
	UPROPERTY(BlueprintReadWrite, Category = "Delay")
		TArray<float> FirstDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		class UDataTable* SecondScriptDT;
	UPROPERTY(BlueprintReadWrite, Category = "Script")
		TArray<FString> SecondScript;
	UPROPERTY(BlueprintReadWrite, Category = "Delay")
		TArray<float> SecondDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		class UDataTable* ThirdScriptDT;
	UPROPERTY(BlueprintReadWrite, Category = "Script")
		TArray<FString> ThirdScript;
	UPROPERTY(BlueprintReadWrite, Category = "Delay")
		TArray<float> ThirdDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		class UDataTable* FourthScriptDT;
	UPROPERTY(BlueprintReadWrite, Category = "Script")
		TArray<FString> FourthScript;
	UPROPERTY(BlueprintReadWrite, Category = "Delay")
		TArray<float> FourthDelay;

private:
	UPROPERTY()
		class AJudgeGameMode* GamemodeRef;

};
