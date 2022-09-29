// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "../../common/public/VRCharacter.h"
#include "LobbyCharacter.generated.h"

/*
 - Name        : ALobbyCharacter
 - Descirption : Lobby 콘텐츠의 메인 Playable 캐릭터
 - Date        : 2022/09/29 LJH
*/

UCLASS()
class DREAMBOX_API ALobbyCharacter : public AVRCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALobbyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//레벨 시퀀스를 초기화
	virtual void InitLevelSequence() override;

	//virtual void OnRPCStartContent(int32 PlayerID, FContentStartInfo StartInfo);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		virtual void PreLoadingEnd() override;

	//크로스 페이드 + 로비 등장 시퀀스 애님
	UFUNCTION(BlueprintImplementableEvent)
		void PlayLevelInitSequence();

	//로비 등장 시퀀스 애님 출력, PlayLobbyInitSequenceAnim에서 호출
	UFUNCTION(BlueprintCallable)
		void PlayLobbyAppearAnim();

public:	
	//로비 등장 효과 애니메이션 시퀀스
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sequence")
		class ULevelSequence* LobbyBeginAnimSequence;

private: 
	//시퀀스 플레이어 : 초기 등장 애님 시퀀스 
	UPROPERTY()
		class ULevelSequencePlayer* LobbyBeginAnimSequencePlayer;
};
