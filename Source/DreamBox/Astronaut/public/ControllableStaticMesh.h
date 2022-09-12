// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautControllableInterface.h"
#include "ControllableStaticMesh.generated.h"

UCLASS()
class DREAMBOX_API AControllableStaticMesh : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AControllableStaticMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 게임모드 미션 state에 제어되는 스태틱 메시 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* DefaultMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* ActivatedMesh;

public:
	// bIsActivated 설정 함수
	UFUNCTION(BlueprintCallable)
		void SetActivation(bool Value);

	// SetActivation(true)가 호출될 시 추가적으로 BP에서 실행할 내용이 있다면 호출
	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
		void OnActivated();

public:
	// 인터페이스에서 상속받은 함수 구현. ControllableStaticMesh에서는 Activate 설정에 사용됨
	virtual void SetStatus_Implementation(bool Value) override;

private:
	// 활성화 상태 저장 변수
	bool bIsActivated;
};
