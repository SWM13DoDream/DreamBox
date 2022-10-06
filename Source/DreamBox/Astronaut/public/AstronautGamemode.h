// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/DreamBoxGameModeBase.h"
#include "AstronautGamemode.generated.h"

/*
 - Name        : AAstronautGamemode
 - Description : ���ֺ���� ���� ���Ӹ��
 - Date        : 2022/07/26 DEVroar
*/

// ���ֺ������ �ӹ� ����� ENUM���� ����
UENUM(BlueprintType)
namespace EAstronautMissionType
{
	enum Type
	{
		// �������� ���� ����
		NONE,

		// Ž�缱 �ӹ� - ���� �������� ����
		LEM,

		// ��ɼ� �ӹ� - �糪 ����Ʈ���̿��� ����
		CSM
	};
}

// ���ֺ���� ��ɼ� �ӹ��� �̵� ����� ENUM���� ���� (LEM �ӹ������� ������� ����)
UENUM(BlueprintType)
namespace EAstronautCSMMoveType
{
	enum Type
	{
		// ���� �۾� - ����ƽ �޽ø� �����鼭 �̵�
		IVA,

		// ���� �۾� - �������� �����ϸ鼭 �̵�
		EVA
	};
}

UCLASS()
class DREAMBOX_API AAstronautGamemode : public ADreamBoxGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// ������ ������ ������ ��� �÷��̾�� ������ ���� RPC ���� (��Ƽ�÷��̾�� ����)
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void PreLoadingEndEvent() override;
	
	virtual void PostLoadingEvent() override;

public:
	// �÷��̾� ĳ���� ���۷���
	class AAstronautCharacter* LocalPlayer;

	// �ӹ� ������ �Ϸ�� ��� true�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bInMission;

/* ��Ƽ�÷��� ���� �ʵ� */
public:
	// ��Ƽ�÷��� ��� ���� (Standalone) & ���� ���� ȣ��Ʈ (ListenServer)�� ����
	ENetMode NetworkingStatus;

	// ����Ʈ �÷��̾� ĳ���� ���۷���
	class AAstronautCharacter* RemotePlayer;

	// ���� ȣ��Ʈ�� ������ �̼�
	int32 HostMission;

	// Ŭ���̾�Ʈ�� ������ �̼�
	int32 ClientMission;

/* ��Ƽ�÷��� ���� �޼��� */
public:
	// �����ϴ� ����Ʈ ������ validity�� üũ�ϰų�, �ִ� ���� ������ �����ϴ� �� ���
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	// ����Ʈ ������ �������� ���� ��� �÷��̾� ���� ���� �� �߰� �۾� ����
	virtual void Logout(AController* Exiting) override;

	// ���� IP �ּҸ� �������� ����
	UFUNCTION(BlueprintCallable)
		FString GetIPAddr();

};
