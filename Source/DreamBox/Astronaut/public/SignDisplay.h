// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautStructBase.h"
#include "AstronautControllableInterface.h"
#include "SignDisplay.generated.h"

/*
 - Name        : ASignDisplay
 - Description : ���� ����� �������� ǥ���� ������ �����ϴ� C++ ����
 - Date        : 2022/09/01 DEVroar
*/

UCLASS()
class DREAMBOX_API ASignDisplay : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASignDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// ǥ���� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* WidgetComponent;

	// SignWidget Ÿ������ �̸� ĳ���õǴ� UserWidget ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class USignWidget* Widget;

public:
	// C++�� BeginPlay�� ȣ��� ���� Ÿ�ֿ̹� BP���� ������ ���� �� �Լ��� ȣ���ϵ��� �ϴ� implementable �Լ�
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void Initialize();

	// ǥ���� ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void SetSignContent(FSignStruct Value);

	// �ü� ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void SetStability(bool Value);

public:
	// �������̽����� ��ӹ��� �Լ� ����. SignDisplay������ Stability ������ ����
	virtual void SetStatus_Implementation(bool Value) override;

private:
	// �ü� ���� ���� ����
	bool bIsStable;
};
