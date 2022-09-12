// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../../common/public/DreamBox.h"
#include "Chair.generated.h"

/*
- Name			: AChair
- Description	: JudgePlayer와 Overlap 시 재판 시작 (TrialBegins)를 호출하는 Actor
- Date			: 2022-08-12
- Version		: 1.0.1 ver
*/

UCLASS()
class DREAMBOX_API AChair : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SitChairFunc(AActor* OtherActor);

public:
	// 의자의 Mesh를 장착하기 위한 MeshComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BODY")
		UStaticMeshComponent* Body;

	// Player와 BeginOverlap을 판단하기 위한 BoxComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BOX")
		UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ARROW")
		class UArrowComponent* Arrow;


private:

	// Player와 Overlap을 확인하기 위한 함수
	UFUNCTION()
		void OnCharacterOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
