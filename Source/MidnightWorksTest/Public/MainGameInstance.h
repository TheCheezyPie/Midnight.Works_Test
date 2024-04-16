// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MIDNIGHTWORKSTEST_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

//  Functions

public:
	void Init() override;

	UFUNCTION()
	void BeginLoadingScreen(const FString& MapName);

	UFUNCTION()
	void EndLoadingScreen(UWorld* InLoadedWorld);

protected:

private:

//  Variables

public:

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading Screen")
	TSubclassOf<class UUserWidget> LoadingScreenWidgetClass;

private:
};
