#pragma once

#include "Engine/DataTable.h"
#include "Engine/Texture.h"
#include "TransitionStructBase.generated.h"

/*
 - Name        : TransitionStructBase
 - Description : Transition/Loading ���� ����ü�� �����ϴ� C++ ���
 - Date        : 2022/09/01 LJH
*/

// FExplanationStruct : ���� ������ �����ϴ� ������ ����ü 
USTRUCT(BlueprintType)
struct FTransitionOptionStruct : public FTableRowBase
{
public:
	GENERATED_USTRUCT_BODY()

	//�ε� ���� Streaming �� ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString TargetLevelName;

	//�ʱ� �ִ� �������� Play �� ������?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bPlayInitialAnimSequence = true; 

	//������ �ִ� �������� Play �� ������?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bPlayFinalAnimSequence = true;
};