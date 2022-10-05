// Fill out your copyright notice in the Description page of Project Settings.


#include "../public/AsyncTestPlayerController.h"
#include "UObject/UObjectGlobals.h"
#include "Kismet/GameplayStatics.h"

void AAsyncTestPlayerController::AsyncLevelLoad(const FString& LevelDir, const FString& LevelName)
{
	LoadPackageAsync(LevelDir + LevelName,
		FLoadPackageAsyncDelegate::CreateLambda([=](const FName & PackageName, UPackage * LoadedPackage, EAsyncLoadingResult::Type Result)
			{
				if (Result == EAsyncLoadingResult::Succeeded)
				{
					AsyncLevelLoadFinished(LevelName);
				}
			}
		),
		0,
		PKG_ContainsMap);
}

void AAsyncTestPlayerController::AsyncLevelLoadFinished(const FString LevelName)
{
	UGameplayStatics::OpenLevel(this, FName(*LevelName));
}
