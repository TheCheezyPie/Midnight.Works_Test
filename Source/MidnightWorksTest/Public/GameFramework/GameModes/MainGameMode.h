// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types.h"

#include "MainGameMode.generated.h"

class APickupSpawner;
class ADoorBase;

UCLASS()
class MIDNIGHTWORKSTEST_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

//  Functions

public:
	void DoorOpened(ADoorBase* Door);

protected:
	virtual void BeginPlay() override;
	void InitializeGame();

	void AllRequiredDoorsOpened();
	void AllDoorsOpened();

private:

//  Variables

public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors")
	TArray<TObjectPtr<ADoorBase>> RequiredDoors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Doors")
	TArray<TObjectPtr<ADoorBase>> AdditionalDoors;

private:
};
