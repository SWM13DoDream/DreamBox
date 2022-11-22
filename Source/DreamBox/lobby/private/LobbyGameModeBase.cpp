// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/LobbyGameModeBase.h"
#include "../../common/public/PersistentLevelBase.h"

void ALobbyGameModeBase::BeginPlay()
{
	Super::BeginPlay(); 
	

}

void ALobbyGameModeBase::PostLogin(APlayerController* NewPlayerController)
{
	Super::PostLogin(NewPlayerController);
}

void ALobbyGameModeBase::PostLoadingEvent()
{
	Super::PostLoadingEvent();
}

void ALobbyGameModeBase::RequestTestResultData(const FString userName, const TArray<float> testResult)
{
	if (testResult.Num() < 6)
	{
		UE_LOG(LogTemp, Warning, TEXT("INVALID DATA"));
		return;
	}
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();

	FString RequestBody;
	FString Key[6] = { "R", "I", "A", "S", "E", "C" };

	RequestObj->SetStringField("name", userName);
	for (int i = 0; i < 6; i++)
	{
		RequestObj->SetStringField(Key[i], FString::FromInt((int)testResult[i]));
	}

	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &ALobbyGameModeBase::OnResponseReceived);
	Request->SetURL("http://13.125.113.112/user"); //DNS로 바꿀 것. 현재는 굉장히 risky 함
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void ALobbyGameModeBase::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	if (!ResponseObj.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Data %s"), *Response->GetContentAsString());
		return; 
	}

	TArray<TSharedPtr<FJsonValue> > responseResult = ResponseObj->GetArrayField("job");

	RecommendationTestResult.Empty();
	for (int resultIdx = 0; resultIdx < responseResult.Num(); resultIdx++)
	{
		RecommendationTestResult.Add(*responseResult[resultIdx]->AsString());
		UE_LOG(LogTemp, Warning, TEXT("job#%d : %s"), resultIdx, *responseResult[resultIdx]->AsString());
	}

	UpdateJobRecommendationList();

	UE_LOG(LogTemp, Display, TEXT("Response %s"), *Response->GetContentAsString());
	//UE_LOG(LogTemp, Display, TEXT("Title : %s"), *jobArr[0]->AsString());
}