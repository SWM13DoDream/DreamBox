// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "MissionManager.generated.h"

/*
 - Name        : AMissionManager
 - Description : �̼� ������ �����ϰ� �ִ� ����. �÷��̾�� �������� ��� ���
 - Date        : 2022/09/04 LJH
*/

UCLASS()
class DREAMBOX_API AMissionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissionManager();

	//�̼�ID�� Variable�� ������� �̼��� �߰� �� ������Ʈ�� ��
	UFUNCTION()
		void UpdateMissionWidgetEvent(int32 MissionID, int32 Variable);

	//�������Ʈ �̺�Ʈ) �̼��� Variable ��ŭ ������Ʈ �Ѵ�
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateMission(int32 MissionID, int32 Variable);

	//�������Ʈ �̺�Ʈ) �̼��� ���� �߰��Ѵ�
	UFUNCTION(BlueprintImplementableEvent)
		void AddNewMission(int32 NewMissionID);

	//�������Ʈ �̺�Ʈ) �̼��� ���� �Ϸ� ��Ų��
	UFUNCTION()
		void RemoveMission(int32 TargetMissionID);

	//�̼� ���� ���۷����� ��ȯ
	UFUNCTION(BlueprintPure)
		UUserWidget* GetMissionWidgetRef() const { return MissionListWidgetRef; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//��Ʈ ������Ʈ
	UPROPERTY()
		USceneComponent* DefaultSceneRoot;
	
	//�̼� ���� ������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* MissionListWidget;

private:
	//�̼� ���� ���۷��� (MissionListWidget->GetWidget())
	UPROPERTY()
		UUserWidget* MissionListWidgetRef;
};
