// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MissionWidget.generated.h"

/*
 - Name        : UMissionWidget
 - Description : ���� ����� �������� �̼� ���� ���̽� C++ �ڵ�
 - Date        : 2022/09/02 DEVroar
*/

UCLASS()
class DREAMBOX_API UMissionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// User Widget �Ļ� Ŭ���� �⺻ ������
	UMissionWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;

public:
	// �̼� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* MainContentText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTextBlock* SubContentText;

	// AstronautCharacter Ÿ������ �̸� ĳ���õǴ� ���� �÷��̾� ���۷���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AAstronautCharacter* LocalPlayer;

public:
	// Gamemode���� ���� �̼� ���� ���� �� ���÷��� ������Ʈ. Unicode�� ����ϹǷ� �Ļ� BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void UpdateMainMissionDisplay();

	// Gamemode���� ���� �̼� ���� ���� �� ���÷��� ������Ʈ. Unicode�� ����ϹǷ� �Ļ� BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void UpdateSubMissionDisplay();
};
