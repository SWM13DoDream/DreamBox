// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "DialogController.generated.h"

/*
 - Name        : ADialogController
 - Description : ���� ����� �������� ���̾�α� ������ �����ϴ� C++ ����
 - Date        : 2022/09/01 DEVroar
*/

UCLASS()
class DREAMBOX_API ADialogController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// ���̾�α� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* WidgetComponent;

	// DialogWidget Ÿ������ �̸� ĳ���õǴ� UserWidget ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class UDialogWidget* Widget;

	// AstronautGamemode Ÿ������ �̸� ĳ���õǴ� Gamemode ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AAstronautGamemode* Gamemode;

public:
	// ���ְ����� ��Ʈ�� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogIntro();
	
	// ���ְ����� Ÿ�̸� �߰� ���� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogMid();

	// ���ְ����� �ӹ� �Ϸ� �ӹ� ���� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogApprox();

	// ���̾�α� ���� �Լ� - BP�� �۾��ϸ� �������� Ŭ���ڵ��� ���� ������
	UFUNCTION(BlueprintCallable)
		void SetDialogContent(FText Value);

private:	
	// Ÿ�̸ӷ� ��ϵǾ� �� �ʸ��� Gamemode�� �ð��� üũ, Ư�� ������ Ÿ �Լ� ȣ��
	FTimerHandle UpdateStateHandler;
	void UpdateState();

	// FSM Concept�� �����Ǵ� ���̾�α� ���� ���� ����
	int32 DialogState;
};
