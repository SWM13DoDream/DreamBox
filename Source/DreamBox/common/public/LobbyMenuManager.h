// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "LobbyMenuManager.generated.h"

/*
 - Name        : ALobbyMenuManager
 - Descirption : 로비 메뉴 UI를 관리하는 액터. 
                 월드상에 배치되어 Visible 유무 처리
 - Date        : 2022/09/19 LJH
*/

UCLASS()
class DREAMBOX_API ALobbyMenuManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALobbyMenuManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void MenuTriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void MenuTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
			, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
		void PlayMenuAnimation(bool bIsBeginAnimation);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		class UUserWidget* GetMenuWidgetRef() const { return MenuWidgetRef; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//본 액터의 루트 Scene 컴포넌트 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		USceneComponent* DefaultSceneRoot; 

	//플레이어에 의해 트리거 되면, 메뉴 UI가 나타남
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		UBoxComponent* MenuTriggerVolume; 

	//메인메뉴 UI 컴포넌트, BP 내에서 클래스를 지정
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay|UI")
		class UWidgetComponent* MenuWidgetComponent; 

private: 
	//메뉴 위젯 레퍼런스
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay|Widget")
		class UUserWidget* MenuWidgetRef;
};
