// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "InfoWidget.generated.h"

/*
 - Name        : UInfoWidget
 - Description : ���� ����� �������� ���� ���� ���̽� C++ �ڵ�
			   : ImplementableEvent ��ɸ� ���ǵǾ��־� �Ļ� BP���� ����
 - Date        : 2022/09/26 DEVroar
*/

UCLASS()
class DREAMBOX_API UInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// User Widget �Ļ� Ŭ���� �⺻ ������
	UInfoWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// ���� �÷��̾�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
		class AAstronautCharacter* LocalPlayer;

	// Ȱ��ȭ ���� ���� (�ַ� ��ư ���ͷ��ǿ��� ���� üũ)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bActivated;

	// ���� Ȱ��ȭ
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "NeedImplementation")
		void Activate();

	// ���� ��Ȱ��ȭ
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "NeedImplementation")
		void Deactivate();
};
