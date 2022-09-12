#pragma once

#include "Engine/DataTable.h"
#include "Engine/Texture.h"
#include "AstronautStructBase.generated.h"

/*
 - Name        : AstronautStructBase
 - Description : 우주 비행사 컨텐츠의 구조체를 관리하는 C++ 헤더
 - Date        : 2022/09/01 DEVroar
*/

// FExplanationStruct : 설명 위젯을 관리하는 데이터 구조체 
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

// FSignStruct : 표지판 위젯을 관리하는 데이터 구조체 
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

// FInteractionStruct : 인터렉션 위젯을 관리하는 데이터 구조체 
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