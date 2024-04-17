// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/GameModes/MainGameMode.h"
#include "Doors/DoorBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/PickupSpawner.h"
#include "Pickups/PickupBase.h"
#include "GameFramework/Controllers/MainPlayerController.h"

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
			if (DoorBase && DoorBase->IsEnabled())
			{
				if (DoorBase->IsRequired())
				{
					RequiredDoors.Add(DoorBase);
				}
				else
				{
					AdditionalDoors.Add(DoorBase);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Door is not enabled"))
			}
		}
	}
}

void AMainGameMode::AllRequiredDoorsOpened()
{
	LOG_SCREEN("All Required Doors Opened");
	AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		PC->RequiredDoorsOpened();
	}
}

void AMainGameMode::AllAdditionalDoorsOpened()
{
	LOG_SCREEN("All Additional Doors Opened");
	AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		PC->AdditionalDoorsOpened();
	}
}

void AMainGameMode::AllDoorsOpened()
{
	LOG_SCREEN("All Doors Opened");
	AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PC)
	{
		PC->AllDoorsOpened();
	}
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

