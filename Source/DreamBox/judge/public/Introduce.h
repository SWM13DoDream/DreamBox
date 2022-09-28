// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Engine/DataTable.h"
#include "Introduce.generated.h"

/*
- Name			: AIntroduce [ 이름변경 요망 ]
- Description	: 각 종 Floating Widget을 담당하는 Actor
- Date			: 2022-09-27 LJH
*/

// 데이터를 담기위한 구조체 생성
USTRUCT(BlueprintType)
struct FWidgetStructure : public FTableRowBase
{
	GENERATED_BODY()

public:
	FWidgetStructure() : Title(""), Description("") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString Description;
};

UCLASS()
class DREAMBOX_API AIntroduce : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIntroduce();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 시나리오에 확장성을 위해 DataTable로 스크립트 저장
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DATA")
		class UDataTable* NData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ROOT")
		USceneComponent* SceneComponent;

	// Float Widget을 의미하는 WidgetComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WIDGET")
		class UWidgetComponent* Widget;

	// Next Page의 여부를 의미하는 WidgetComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WIDGET")
		class UWidgetComponent* NextPage;

	// Next Page의 여부를 확인하는 Boolean 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WIDGET")
		bool isNextPage;

	UPROPERTY()
		class AJudgeGameMode* GamemodeRef;

};
