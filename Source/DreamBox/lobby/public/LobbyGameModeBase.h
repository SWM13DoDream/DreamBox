// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/DreamBoxGameModeBase.h"
#include "Http.h"
#include "Json.h"
#include "LobbyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DREAMBOX_API ALobbyGameModeBase : public ADreamBoxGameModeBase
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayerController) override; 

	virtual void PostLoadingEvent() override; 

public:
	UFUNCTION(BlueprintCallable)
		void RequestTestResultData(const FString userName, const TArray<float> testResultData); //Listen-Server ��ݿ����� ����? -> Gamemode�� �ƴ� ��ü System Actor ���� �ʿ�

	//UFUNCTION(BlueprintCallable)
		void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdateJobRecommendationList();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		TArray<FString> RecommendationTestResult;
};
