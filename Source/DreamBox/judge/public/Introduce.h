// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Engine/DataTable.h"
#include "Introduce.generated.h"

/*
- Name			: AIntroduce [ �̸����� ��� ]
- Description	: �� �� Floating Widget�� ����ϴ� Actor
- Date			: 2022-09-27 LJH
*/

// �����͸� ������� ����ü ����
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
	// �ó������� Ȯ�强�� ���� DataTable�� ��ũ��Ʈ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DATA")
		class UDataTable* NData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ROOT")
		USceneComponent* SceneComponent;

	// Float Widget�� �ǹ��ϴ� WidgetComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WIDGET")
		class UWidgetComponent* Widget;

	// Next Page�� ���θ� �ǹ��ϴ� WidgetComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WIDGET")
		class UWidgetComponent* NextPage;

	// Next Page�� ���θ� Ȯ���ϴ� Boolean ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WIDGET")
		bool isNextPage;

	UPROPERTY()
		class AJudgeGameMode* GamemodeRef;

};
