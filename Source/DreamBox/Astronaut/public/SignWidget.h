// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AstronautStructBase.h"
#include "SignWidget.generated.h"

/*
 - Name        : USignWidget
 - Description : ���� ����� �������� ǥ���� ���� ���̽� C++ �ڵ�
 - Date        : 2022/09/02 DEVroar
*/

UCLASS()
class DREAMBOX_API USignWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// User Widget �Ļ� Ŭ���� �⺻ ������
	USignWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// ǥ���� ������ ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* SubtitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* DescriptionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* StateText;

public:
	// ��� ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void SetIdentity(FSignStruct Value);

	// �ü� ���¿� ���� StateText�� �����ϴ� �Լ�. SlateColor ����� ���� �Ļ� BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void SetStateDisplay(bool bIsStable);

public:
	// ǥ���� ������ ���� (SignStruct ����ü ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSignStruct Content;
};
