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

protected:
	virtual void BeginPlay() override;
	void InitializeGame();

private:

//  Variables

public:

protected:

private:
};
