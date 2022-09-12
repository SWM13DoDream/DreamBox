// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "AstronautControllableInterface.h"
#include "AstronautDestinationGuide.generated.h"

UCLASS()
class DREAMBOX_API AAstronautDestinationGuide : public AActor, public IAstronautControllableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstronautDestinationGuide();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 스태틱 메시 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* CylinderMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* ConeMesh;

public:
	// Visibility 설정 함수
	UFUNCTION(BlueprintCallable)
		void SetVisibility(bool Value);

public:
	// 인터페이스에서 상속받은 함수 구현. AstronautDestinationGuide에서는 Visibility 설정에 사용됨
	virtual void SetStatus_Implementation(bool Value) override;
};
