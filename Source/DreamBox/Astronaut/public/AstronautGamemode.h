// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/DreamBoxGameModeBase.h"
#include "AstronautGamemode.generated.h"

/*
 - Name        : AAstronautGamemode
 - Description : 우주비행사 메인 게임모드
 - Date        : 2022/07/26 DEVroar
*/

// 우주비행사의 임무 목록을 ENUM으로 관리
UENUM(BlueprintType)
namespace EAstronautMissionType
{
	enum Type
	{
		// 선택하지 않은 상태
		NONE,

		// 탐사선 임무 - 월면 기지에서 수행
		LEM,

		// 사령선 임무 - 루나 게이트웨이에서 수행
		CSM
	};
}

// 우주비행사 사령선 임무의 이동 방식을 ENUM으로 관리 (LEM 임무에서는 사용하지 않음)
UENUM(BlueprintType)
namespace EAstronautCSMMoveType
{
	enum Type
	{
		// 선내 작업 - 스태틱 메시를 잡으면서 이동
		IVA,

		// 선외 작업 - 생명줄을 고정하면서 이동
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

	// 유저가 레벨에 참가한 경우 플레이어에게 컨텐츠 시작 RPC 전송 (멀티플레이어와 무관)
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void PreLoadingEndEvent() override;
	
	virtual void PostLoadingEvent() override;

public:
	// 플레이어 캐릭터 레퍼런스
	class AAstronautCharacter* LocalPlayer;

	// 임무 선택이 완료된 경우 true로 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bInMission;

/* 멀티플레이 관련 필드 */
public:
	// 멀티플레이 사용 안함 (Standalone) & 리슨 서버 호스트 (ListenServer)로 구분
	ENetMode NetworkingStatus;

	// 리모트 플레이어 캐릭터 레퍼런스
	class AAstronautCharacter* RemotePlayer;

	// 서버 호스트가 선택한 미션
	int32 HostMission;

	// 클라이언트가 선택한 미션
	int32 ClientMission;

/* 멀티플레이 관련 메서드 */
public:
	// 입장하는 리모트 유저의 validity를 체크하거나, 최대 입장 제한을 설정하는 데 사용
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	// 리모트 유저가 서버에서 나간 경우 플레이어 정보 제거 등 추가 작업 진행
	virtual void Logout(AController* Exiting) override;

	// 로컬 IP 주소를 가져오는 로직
	UFUNCTION(BlueprintCallable)
		FString GetIPAddr();

};
