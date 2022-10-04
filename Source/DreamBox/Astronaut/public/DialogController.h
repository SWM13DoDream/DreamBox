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

	// AstronautCharacter Ÿ������ �̸� ĳ���õǴ� ���� �÷��̾� ���۷���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control")
		class AAstronautCharacter* LocalPlayer;

	// ��簡 ����ǰ� �ִ� ������ �ٸ� ��簡 ����� �� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDialogLock;

	// ���õ� ���ֺ���� �ӹ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Mission;

	// ��Ƽ�÷��̾� ��, �ٸ� �÷��̾�κ��� ���� �޽����� �� ��� ��ġ�� �ʵ��� register
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bDoneMessageRegistered;

	// ���ֺ���� ��Ƽ�÷��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bInMultiplay;

	// ���ֺ���� ��Ƽ�÷��� ���� ���̾�α� ǥ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bMultiplayDialogFlag;

public:
	// ���̾�α� ��Ʈ�ѷ� ������ Ȱ��ȭ ���� ����
	UFUNCTION(BlueprintCallable)
		void SetActivated(bool bValue, int32 SelectedMission, bool bMultiplay);

	// ���ֺ���� LEM ��Ʈ�� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogIntro();
	
	// ���ֺ���� LEM Ÿ�̸� �߰� ���� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogMid();

	// ���ֺ���� LEM �ӹ� �Ϸ� �ӹ� ���� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void LEMDialogApprox();

	// ���ֺ���� CSM ��Ʈ�� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void CSMDialogIntro();

	// ���ֺ���� CSM �߰� ���� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void CSMDialogMid();

	// ���ֺ���� ��Ƽ�÷��� LEM ���� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void LEMMultiplayIntro();

	// ���ֺ���� ��Ƽ�÷��� LEM ��� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void LEMDoneMessageFromCSM();

	// ���ֺ���� ��Ƽ�÷��� CSM ��� ���̾�α� �̺�Ʈ. BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event")
		void CSMDoneMessageFromLEM();

	// ���̾�α� ���� �Լ� - BP�� �۾��ϸ� �������� Ŭ���ڵ��� ���� ������
	UFUNCTION(BlueprintCallable)
		void SetDialogContent(FText Value);

	// ��Ƽ�÷��̿��� �ٸ� �÷��̾��� �ӹ��� ������ �� DoneMessageDialog ���
	UFUNCTION(BlueprintCallable)
		void AnnounceMissionDoneFromOther();

private:	
	// Ÿ�̸ӷ� ��ϵǾ� �� �ʸ��� Gamemode�� �ð��� üũ, Ư�� ������ Ÿ �Լ� ȣ��
	FTimerHandle UpdateStateHandler;
	void UpdateState();

	// FSM Concept�� �����Ǵ� ���̾�α� ���� ���� ����
	int32 DialogState;
};
