#pragma once

#include "Engine/DataTable.h"
#include "Engine/Texture.h"
#include "AstronautStructBase.generated.h"

/*
 - Name        : AstronautStructBase
 - Description : ���� ����� �������� ����ü�� �����ϴ� C++ ���
 - Date        : 2022/09/01 DEVroar
*/

// FExplanationStruct : ���� ������ �����ϴ� ������ ����ü 
USTRUCT(BlueprintType)
struct FExplanationStruct : public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Subtitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText NavUpperTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText NavUpperContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText NavLowerTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText NavLowerContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture* Image;
};

// FSignStruct : ǥ���� ������ �����ϴ� ������ ����ü 
USTRUCT(BlueprintType)
struct FSignStruct : public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Subtitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
};

// FInteractionStruct : ���ͷ��� ������ �����ϴ� ������ ����ü 
USTRUCT(BlueprintType)
struct FInteractionStruct : public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Content;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Confirmation;
};