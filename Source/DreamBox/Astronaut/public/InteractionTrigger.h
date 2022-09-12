// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautStructBase.h"
#include "AstronautControllableInterface.h"
#include "InteractionTrigger.generated.h"

/*
 - Name        : AInteractionTrigger
 - Description : ���� ����� �������� ���ͷ��� ������ �����ϴ� C++ ����
 - Date        : 2022/09/02 DEVroar
*/

UCLASS()
class DREAMBOX_API AInteractionTrigger : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// ���ͷ��� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		class UWidgetComponent* WidgetComponent;

	// ���ͷ��� �ڽ� �ݸ��� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UBoxComponent* BoxCollision;

	// InteractionWidget Ÿ������ �̸� ĳ���õǴ� UserWidget ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class UInteractionWidget* Widget;

	// AstronautGamemode Ÿ������ �̸� ĳ���õǴ� Gamemode ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AAstronautGamemode* Gamemode;

public:
	// �� C++���� BeginPlay ȣ�� �� BP���� �Ļ��� InitializeMode() �̺�Ʈ ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void InitializeMode();

	// ���� ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
		void SetInteractionContent(FInteractionStruct Content);

	// BoxTrigger�� ���� ���� �� ȣ��Ǵ� �Լ�, ���� C++���� Validity ó���� �ѹ��� ������
	UFUNCTION(BlueprintCallable)
		void OnTriggerEnter(class AActor* OtherActor);

	// BoxTrigger���� ���� ���� �� ȣ��Ǵ� �Լ�, ���� C++���� Validity ó���� �ѹ��� ������
	UFUNCTION(BlueprintCallable)
		void OnTriggerExit(class AActor* OtherActor);

	// �ڽ� ������ ��ư�� ������ �� ȣ��Ǵ� �Լ�
	UFUNCTION(BlueprintCallable)
		void OnInteract();

	// bIsInteractable�� false�� �����ϰ� �̼� ���̵� ���͸� ��Ȱ��ȭ�ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
		void Unset();

public:
	// ���ͷ��� ��� (D_Interaction�� key��)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName InteractionMode;

	// ��ȣ�ۿ� ������ �������� Ȯ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsInteractable;

	// �ڽ� ������ Ȱ��ȭ�� �������� Ȯ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsAvailable;

	// ���ͷ��� ������ �ٲ� �� �ִ� InteractionTrigger �ν��Ͻ����� Ȯ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bHasVariableMode;

public:
	// �������̽����� ��ӹ��� �Լ� ����. InteractionTrigger������ Unset ������ ����
	virtual void SetStatus_Implementation(bool Value) override;

private:
	// UE4 C++���� Delay ����� ���� Ÿ�̸� �ڵ鷯
	FTimerHandle DelayHandler;

	// Trigger ��� �÷��̾� ������ Validity üũ
	bool IsValidPlayer(class AActor* TargetActor);
};
