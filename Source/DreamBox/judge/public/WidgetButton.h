// Fill out your copyright notice in the Description page of Project Settings.

/*
- Name			: AWidgetButton
- Description	: �� 3D Floating Widget�� �����ϱ� ���� Button Actor
- Date			: 2022-09-06
*/

#pragma once

#include "../../common/public/DreamBox.h"
#include "WidgetButton.generated.h"


UCLASS()
class DREAMBOX_API AWidgetButton : public AActor
{
	GENERATED_BODY()

public:
	AWidgetButton();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, Category = "ROOT")
		USceneComponent* DefaultSceneRoot;

	// BODY�� ���� StaticMeshComponent
	UPROPERTY(VisibleAnywhere, Category = "BODY")
		UStaticMeshComponent* Body;

	// NameWidget�� ���� Name ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NAME")
		FText Name;

	// 3D Float Widget ���� ��ư ���� ButtonWidget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BUTTON")
		class UWidgetComponent* ButtonWidget;

	// Widget�� ������ ���� NameWiget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NAME_WIDGET")
		class UWidgetComponent* NameWidget;
};
