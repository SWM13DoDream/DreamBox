// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "ScriptManager.generated.h"

/*
 - Name        : AScriptManager
 - Description : 스크립트 위젯을 소유하고 있는 액터. 플레이어와 위젯간의 통신 경로
 - Date        : 2022/09/04 LJH
*/

UCLASS()
class DREAMBOX_API AScriptManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScriptManager();
	
	//블루프린트 이벤트) ID를 기반으로 스크립트를 호출
	UFUNCTION(BlueprintImplementableEvent)
		void ShowScriptWithID(int32 ScriptID);

	//블루프린트 이벤트) 임의의 스트링을 기반으로 스크립트를 호출
	UFUNCTION(BlueprintImplementableEvent)
		void ShowScriptWithString(const FString& Script);

	//스크립트 위젯 레퍼런스를 반환
	UFUNCTION(BlueprintPure)
		UUserWidget* GetScriptWidgetRef() const { return ScriptWidgetRef; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//루트 컴포넌트
	UPROPERTY()
		USceneComponent* DefaultSceneRoot;
	
	//스크립트 위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* ScriptWidget; 

	//음성 더빙 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* VoiceDubbing;

private:
	//스크립트 위젯의 레퍼런스 (ScriptWidget->GetWidget())
	UPROPERTY()
		UUserWidget* ScriptWidgetRef;
};
