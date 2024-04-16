// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/GameModes/MainGameMode.h"
#include "Doors/DoorBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/PickupSpawner.h"
#include "Pickups/PickupBase.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeGame();
}

void AMainGameMode::InitializeGame()
{
	TArray<AActor*> Doors;

	UGameplayStatics::GetAllActorsOfClass(this, ADoorBase::StaticClass(), Doors);
}
