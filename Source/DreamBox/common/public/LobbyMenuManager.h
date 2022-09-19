// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DreamBox.h"
#include "LobbyMenuManager.generated.h"

/*
 - Name        : ALobbyMenuManager
 - Descirption : �κ� �޴� UI�� �����ϴ� ����. 
                 ����� ��ġ�Ǿ� Visible ���� ó��
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
	//�� ������ ��Ʈ Scene ������Ʈ 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		USceneComponent* DefaultSceneRoot; 

	//�÷��̾ ���� Ʈ���� �Ǹ�, �޴� UI�� ��Ÿ��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
		UBoxComponent* MenuTriggerVolume; 

	//���θ޴� UI ������Ʈ, BP ������ Ŭ������ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay|UI")
		class UWidgetComponent* MenuWidgetComponent; 

private: 
	//�޴� ���� ���۷���
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay|Widget")
		class UUserWidget* MenuWidgetRef;
};
