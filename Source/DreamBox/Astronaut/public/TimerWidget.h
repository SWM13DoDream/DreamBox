// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AstronautGamemode.h"
#include "TimerWidget.generated.h"

/*
 - Name        : UTimerWidget
 - Description : ���� ����� �������� Ÿ�̸� ���� ���̽� C++ �ڵ�
 - Date        : 2022/09/02 DEVroar
*/

UCLASS()
class DREAMBOX_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// User Widget �Ļ� Ŭ���� �⺻ ������
	UTimerWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

protected:
	// TitleText�� ǥ�õǴ� TEXT �����. �Ļ� BP���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText TITLE_DONEABLE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Constant)
		FText TITLE_NOT_DONEABLE;
	
public:
	// Ÿ�̸� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* TitleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* ContentText;

	// AstronautGamemode Ÿ������ �̸� ĳ���õǴ� Gamemode ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AAstronautGamemode* Gamemode;

public:
	// Gamemode���� �� �ʸ��� ȣ��Ǿ� Ÿ�̸� ���÷��� üũ
	UFUNCTION(BlueprintCallable)
		void UpdateDisplay();

	// UpdateDisplay ȣ�� �ø��� OuterWidget�� ���� �����̼� ����, �Ļ� BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void ChangeTimerRotation(float Angle);

	// Gamemode->bIsAboardable ������ �ٲ� �� SlateColor�� �̿��� ������ �ؽ�Ʈ ���� ����, �Ļ� BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void ChangeTimeColor(bool bIsAboardable);

private:
	// ChangeTimeColor�� ���� ���� (Rising/Falling) �ÿ��� ȣ���ϵ��� �ϴ� aboardable ���� ���� ���� ����
	bool bWasAboardable;
};
