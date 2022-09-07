// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "ScriptManager.generated.h"

/*
 - Name        : AScriptManager
 - Description : ��ũ��Ʈ ������ �����ϰ� �ִ� ����. �÷��̾�� �������� ��� ���
 - Date        : 2022/09/04 LJH
*/

UCLASS()
class DREAMBOX_API AScriptManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScriptManager();
	
	//�������Ʈ �̺�Ʈ) ID�� ������� ��ũ��Ʈ�� ȣ��
	UFUNCTION(BlueprintImplementableEvent)
		void ShowScriptWithID(int32 ScriptID);

	//�������Ʈ �̺�Ʈ) ������ ��Ʈ���� ������� ��ũ��Ʈ�� ȣ��
	UFUNCTION(BlueprintImplementableEvent)
		void ShowScriptWithString(const FString& Script);

	//��ũ��Ʈ ���� ���۷����� ��ȯ
	UFUNCTION(BlueprintPure)
		UUserWidget* GetScriptWidgetRef() const { return ScriptWidgetRef; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//��Ʈ ������Ʈ
	UPROPERTY()
		USceneComponent* DefaultSceneRoot;
	
	//��ũ��Ʈ ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* ScriptWidget; 

	//���� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* VoiceDubbing;

private:
	//��ũ��Ʈ ������ ���۷��� (ScriptWidget->GetWidget())
	UPROPERTY()
		UUserWidget* ScriptWidgetRef;
};
