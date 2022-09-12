// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../common/public/DreamBox.h"
#include "FloatSign.generated.h"

UCLASS()
class DREAMBOX_API AFloatSign : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloatSign();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ROOT")
		USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BOX")
		UBoxComponent* Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WIDGET")
		class UWidgetComponent* Screen;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WIDGET")
		class UWidgetComponent* Question;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TOGGLE")
		bool bToggle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TITLE")
		FText TitleText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DESCRIPTION")
		FText DescriptionText;

public:
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
