// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "InjuredCharacter.generated.h"

/*
 - Name        : AInjuredCharacter
 - Description : 캐릭터가 구조할 요구조자 캐릭터
 - Date        : 2022/09/05 LJH
*/

UCLASS()
class DREAMBOX_API AInjuredCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInjuredCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//플레이어가 가까이 왔음을 체크. 가까이 왔다면(볼륨 내에 들어왔다면) Carry 인터렉션이 가능하도록 업데이트
	UFUNCTION()
		void InteractionTriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp
								, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//플레이어가 멀리갔음을 체크. 볼륨 밖으로 나갔다면 Carry 인터렉션이 불가능하도록 업데이트
	UFUNCTION()
		void InteractionTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* otherActor
								, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//캐릭터가 플레이어에게 업혀있는 동안에는 콜리전을 제거한다. 
	UFUNCTION()
		void SetCharacterCollisionState(bool NewState);

	//구조되고 있는지 업데이트 (애니메이션 업데이트 위함)
	UFUNCTION()
		void SetIsBeingRescued(bool NewState);

	//미션 추가 이벤트에 바인딩 되어서, 할당된 ID에 맞는 미션이 추가되면 이 액터를 Activate
	UFUNCTION()
		void TryActivateMissionActor(int TargetPlayerId, int NewMissionId, int32 Variable);

	UFUNCTION(BlueprintImplementableEvent)
		void PlayWidgetAnimtion(bool bIsStart);

	/* --- Get/Set 함수 ----- */
	UFUNCTION(BlueprintPure)
		bool GetIsBeingRescued() { return bIsBeingRescued; }
	
	UFUNCTION(BlueprintCallable)
		void SetIsRescued(bool NewState) { bIsRescued = NewState; }

	UFUNCTION(BlueprintCallable)
		bool GetIsRescued() { return bIsRescued; }

	UFUNCTION()
		int32 GetMissionID() { return MissionID; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//인터렉션이 가능한 범위를 나타내고 오버랩 이벤트를 통해 체크
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* InteractionTrigger;

	//가이드 메시 컴포넌트
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* RescueGuideMesh;

	//미션을 진행하기 위한 정보를 담은 위젯 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* InfoWidget;

	//바인딩할 미션의 ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mission")
		int32 MissionID;

private:
	//소방관 게임모드 레퍼런스
	UPROPERTY()
		class AFirefighterGamemode* GamemodeRef; 

	//현재 구조되고 있는지?
	UPROPERTY()
		bool bIsBeingRescued = false ;
	
	//이미 구조 되었는지?
	UPROPERTY()
		bool bIsRescued =  false;

	//Activate 되었는지? (=상호작용이 가능한지?)
	UPROPERTY()
		bool bIsActivated = false;
};
