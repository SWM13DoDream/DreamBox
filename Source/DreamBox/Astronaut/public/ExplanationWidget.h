// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "AstronautStructBase.h"
#include "ExplanationWidget.generated.h"

/*
 - Name        : UExplanationWidget
 - Description : ���� ����� �������� ���� ���� ���̽� C++ �ڵ�
 - Date        : 2022/09/01 DEVroar
*/

UCLASS()
class DREAMBOX_API UExplanationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// User Widget �Ļ� Ŭ���� �⺻ ������
	UExplanationWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// ���� ������ ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* SubtitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* NavUpperTitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* NavUpperContentText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* NavLowerTitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* NavLowerContentText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* DescriptionText;

public:
	// ��� ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void SetIdentity(FExplanationStruct Value);

	// �̹��� ���� �Լ�, BP Slate Brush ��� ����� ���� �Ļ� BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void SetImage(UTexture* Texture);

public:
	// ���� ������ ���� (ExplanationStruct ����ü ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FExplanationStruct Content;
};
