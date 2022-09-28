#pragma once

#include "Engine/DataTable.h"
#include "Engine/Texture.h"
#include "TransitionStructBase.generated.h"

/*
 - Name        : TransitionStructBase
 - Description : Transition/Loading 관련 구조체를 관리하는 C++ 헤더
 - Date        : 2022/09/27 LJH
*/

// FExplanationStruct : 설명 위젯을 관리하는 데이터 구조체 
USTRUCT(BlueprintType)
struct FTransitionOptionStruct : public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	//로딩 이후 Streaming 할 레벨명
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString TargetLevelName;

	//초기 애님 시퀀스를 Play 할 것인지?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bPlayInitialAnimSequence = true; 

	//마지막 애님 시퀀스를 Play 할 것인지?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bPlayFinalAnimSequence = true;
};


//FContentStartInfo : 로딩 이후 콘텐츠가 시작될 때 각 클라이언트에 전달할 데이터
USTRUCT(BlueprintType)
struct FContentStartInfo : public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FQuat StartRotation;
};
