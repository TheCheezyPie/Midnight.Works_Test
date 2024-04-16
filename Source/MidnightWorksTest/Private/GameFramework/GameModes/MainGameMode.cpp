// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/GameModes/MainGameMode.h"
#include "Doors/DoorBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/PickupSpawner.h"
#include "Pickups/PickupBase.h"

void AMainGameMode::SpawnPickups(const FName& DoorName, const TMap<EPickupType, int32>& PickupsToSpawn)
{
	TArray<AActor*> PickupSpawners;

	UGameplayStatics::GetAllActorsOfClassWithTag(this, APickupSpawner::StaticClass(), DoorName, PickupSpawners);
	if (PickupSpawners.Num() > 0)
	{
		TArray<APickupSpawner*> KeySpawners;
		TArray<APickupSpawner*> CoinSpawners;

		for (AActor* Actor : PickupSpawners)
		{
			APickupSpawner* Spawner = StaticCast<APickupSpawner*>(Actor);

			switch (Spawner->GetPickupType())
			{
			case EPickupType::Key:
				KeySpawners.Add(Spawner);
				break;
			case EPickupType::Coin:
				CoinSpawners.Add(Spawner);
				break;
			default:
				break;
			}
		}

		for (const auto& Pair : PickupsToSpawn)
		{
			switch (Pair.Key)
			{
			case EPickupType::Key:
				if (KeySpawners.Num() > 0)
				{
					int32 Index = FMath::RandRange(0, KeySpawners.Num() - 1);
					KeySpawners[Index]->SpawnPickup(EPickupType::Key);
					KeySpawners.RemoveAt(Index);
				}
				break;
			case EPickupType::Coin:
				if (CoinSpawners.Num() > 0)
				{
					int32 Index = FMath::RandRange(0, CoinSpawners.Num() - 1);
					CoinSpawners[Index]->SpawnPickup(EPickupType::Coin);
					CoinSpawners.RemoveAt(Index);
				}
				break;
			default:
				break;
			}
		}
	}
}

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
