// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "ScriptManager.generated.h"

UCLASS()
class DREAMBOX_API AScriptManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScriptManager();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowScriptWithID(int32 ScriptID);

	UFUNCTION(BlueprintImplementableEvent)
		void ShowScriptWithString(const FString& Script);

	UFUNCTION(BlueprintPure)
		UUserWidget* GetScriptWidgetRef() const { return ScriptWidgetRef; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY()
		USceneComponent* DefaultSceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* ScriptWidget; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* VoiceDubbing;

private:
	UPROPERTY()
		UUserWidget* ScriptWidgetRef;
};
