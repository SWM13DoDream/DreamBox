// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AstronautStructBase.h"
#include "InteractionWidget.generated.h"

/*
 - Name        : UInteractionWidget
 - Description : ���� ����� �������� ���ͷ��� ���� ���̽� C++ �ڵ�
 - Date        : 2022/09/02 DEVroar
*/

UCLASS()
class DREAMBOX_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// User Widget �Ļ� Ŭ���� �⺻ ������
	UInteractionWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// �̼� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* IntroductionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* InteractionText;

	// �ش� ������ ������Ʈ�� ������ InteractionTrigger ���� ����.
	// �� ������ ���� InteractionTrigger�� BeginPlay���� �ʱ�ȭ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AInteractionTrigger* Controller;

public:
	// ��� ���� �� ���� ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void SetIdentity(class AInteractionTrigger* Parent, FInteractionStruct Value);

	// ���ͷ��� ��ư�� ������ �� ȣ��Ǵ� �Լ�. InteractionTrigger�� ��� �޼��� ȣ��
	UFUNCTION(BlueprintCallable)
		void OnInteract();

	// ���� �ִϸ��̼� ���. �Ļ� BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void Animate(bool bIsAppearing);

private:
	// ���ͷ��� ���� ����
	FInteractionStruct Content;
};
