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

	for (AActor* Door : Doors)
	{
		if (Door)
		{
			ADoorBase* DoorBase = StaticCast<ADoorBase*>(Door);
			if (DoorBase->IsRequired())
			{
				RequiredDoors.Add(DoorBase);
			}
			else
			{
				AdditionalDoors.Add(DoorBase);
			}
		}
	}
}

void AMainGameMode::AllRequiredDoorsOpened()
{
	LOG_SCREEN("All Required Doors Opened");
}

void AMainGameMode::AllAdditionalDoorsOpened()
{
	LOG_SCREEN("All Additional Doors Opened");
}

void AMainGameMode::AllDoorsOpened()
{
	LOG_SCREEN("All Doors Opened");
}

void AMainGameMode::DoorOpened(ADoorBase* Door)
{
	if (Door)
	{
		if (Door->IsRequired())
		{
			RequiredDoors.Remove(Door);
		}
		else
		{
			AdditionalDoors.Remove(Door);
		}
	}

	if (RequiredDoors.Num() == 0 && AdditionalDoors.Num() == 0)
	{
		AllDoorsOpened();
	}
	else if (RequiredDoors.Num() == 0)
	{
		AllRequiredDoorsOpened();
	}
	else if (AdditionalDoors.Num() == 0)
	{
		AllAdditionalDoorsOpened();
	}
}

