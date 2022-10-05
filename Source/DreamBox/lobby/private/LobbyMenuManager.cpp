// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/LobbyMenuManager.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ALobbyMenuManager::ALobbyMenuManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DEFAULT_SCENE_ROOT"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	MenuTriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("MENU_TRIGGER"));
	MenuTriggerVolume->SetupAttachment(DefaultSceneRoot);
	MenuTriggerVolume->SetRelativeLocation({ 100.0f, 0.0f, 0.0f });
	MenuTriggerVolume->SetRelativeScale3D({ 1.0f, 1.75f, 3.0f });

	MenuTriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MENU_TRIGGER_MESH"));
	MenuTriggerMesh->SetupAttachment(DefaultSceneRoot);

	MenuWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("MENU_WIDGET"));
	MenuWidgetComponent->SetupAttachment(DefaultSceneRoot);
	MenuWidgetComponent->SetRelativeScale3D(FVector(0.15f));
	MenuWidgetComponent->SetDrawSize({ 3520, 960 });
	MenuWidgetComponent->SetGeometryMode(EWidgetGeometryMode::Cylinder);
	MenuWidgetComponent->SetCylinderArcAngle(120.0f);
}

// Called when the game starts or when spawned
void ALobbyMenuManager::BeginPlay()
{
	Super::BeginPlay();
	
	MenuWidgetRef = MenuWidgetComponent->GetWidget();
	MenuTriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ALobbyMenuManager::MenuTriggerBeginOverlap);
	MenuTriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ALobbyMenuManager::MenuTriggerEndOverlap);
}

// Called every frame
void ALobbyMenuManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALobbyMenuManager::MenuTriggerBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player")) return; //플레이어 유효성 검사
	PlayMenuAnimation(true);
}

void ALobbyMenuManager::MenuTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
	, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || !OtherActor->ActorHasTag("Player")) return; //플레이어 유효성 검사
	PlayMenuAnimation(false);
}