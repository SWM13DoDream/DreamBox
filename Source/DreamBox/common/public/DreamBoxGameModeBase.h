// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../../common/public/DreamBox.h"
#include "GameFramework/GameModeBase.h"
#include "DreamBoxGameModeBase.generated.h"

/* 
 - Name        : ADreamBoxGamemode
 - Descirption : ���� ���Ӹ�� ���̽�, ���� ��Ʈ���� ���� ������ �������
 - Date        : 2022/09/03 LJH
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleDynamicOneParam, int32, PlayerID);


UCLASS()
class DREAMBOX_API ADreamBoxGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	//�ε�(������ ���� ��Ʈ����)�� ���� ������ ȣ��Ǵ� �̺�Ʈ 
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicOneParam LoadingEndEvent;

	//CrossFade �ִϸ��̼��� ���
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
		FDeleDynamicOneParam CrossFadeAnimationEvent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//�ε��� ���� ������ BeginPlay �̺�Ʈ
	UFUNCTION()
		virtual void BeginPlayAfterLoading(int32 PlayerID);

	//���� �������� �ʱ�ȭ
	UFUNCTION()
		void InitLevelSequence();

	//ũ�ν� ���̵带 ������ ����ϴ� ����, �� �ڽ� ���Ӹ�� Ŭ�������� ���ε� �ؾ���
	UFUNCTION(BlueprintCallable)
		virtual void PlayCrossFadeAnim(int32 PlayerID);

public:
	//ũ�ν� ���̵� ȿ�� 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* CrossFade;

private:
	//������ �÷��̾�
	UPROPERTY()
		class ULevelSequencePlayer* CrossFadePlayer;
};
