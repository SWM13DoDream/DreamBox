// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautControllableInterface.h"
#include "GameFramework/Actor.h"
#include "GrabUserDisplay.generated.h"

/*
 - Name			: AGrabUserDisplay
 - Author		: DEVroar
 - Descirption	: 우주비행사 CSM 임무에서 Grip이 제대로 동작했는지 확인하는 디스플레이
 - Date			: 2022/09/29
*/

UCLASS()
class DREAMBOX_API AGrabUserDisplay : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabUserDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Root Component 설정을 위한 빈 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		USphereComponent* EmptyComponent;

	// Grip 영역을 나타내는 Animating Sphere 스태틱 메시 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* SphereMesh;

	// Grip 당기기를 나타내는 화살표 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UArrowComponent* ForceArrow;

protected:
	// 해당 Grip을 이용하고 있는 actor 레퍼런스
	class AAstronautCharacter* PlayerActor;
	AActor* HandActor;
	bool bLeft;

	// Activate 시의 Display 위치. Arrow Length 표현에 사용
	FVector LocationWhenActivated;

	// 1초마다 실행되는 타이머 핸들러
	void DisplayTick();
	FTimerHandle DisplayTickHandler;

public:
	// 액터의 기본 컨트롤러 액터를 등록 (PlayerActor, HandActor)
	UFUNCTION(BlueprintCallable)
		void Initialize(AActor* Player, AActor* Hand, bool bIsLeft);

	// 액터 활성화
	void ActivateDisplay(bool bEnableArrow);

public:
	// 인터페이스에서 상속받은 함수 구현. GrabUserDisplay에서는 false를 받았을 때에 한해 액터를 비활성화
	virtual void SetStatus_Implementation(bool Value) override;

	// 인터페이스에서 상속받은 함수 구현
	virtual AActor* GetActor_Implementation() override;
};
