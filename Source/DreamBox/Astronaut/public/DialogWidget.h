// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DialogWidget.generated.h"

/*
 - Name        : UDialogWidget
 - Description : ���� ����� �������� ���̾�α� ���� ���̽� C++ �ڵ�
 - Date        : 2022/09/01 DEVroar
*/

UCLASS()
class DREAMBOX_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// User Widget �Ļ� Ŭ���� �⺻ ������
	UDialogWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// ���̾�α� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* ContentText;

public:
	// ��� ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void SetIdentity(FText Value);

public:
	// ���̾�α� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Content;
};
