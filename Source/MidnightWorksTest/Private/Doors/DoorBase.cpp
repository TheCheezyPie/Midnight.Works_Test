// Fill out your copyright notice in the Description page of Project Settings.


#include "Doors/DoorBase.h"
#include "GameFramework/GameModes/MainGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/PickupBase.h"
#include "Pickups/PickupSpawner.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "UMG/DoorWidget.h"

ADoorBase::ADoorBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetupAttachment(GetRootComponent());

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(FrameMesh);

	FrontArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("FrontArrow"));
	FrontArrow->SetupAttachment(GetRootComponent());

	RequiredPickupsWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("RequiredPickupsWidget"));
	RequiredPickupsWidget->SetupAttachment(GetRootComponent());
}

void ADoorBase::BeginPlay()
{
	Super::BeginPlay();

	DoorWidget = Cast<UDoorWidget>(RequiredPickupsWidget->GetWidget());
	InitializeDoor();
}

void ADoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorBase::AddPickup(EPickupType Type, int32 Value)
{
	int32 RequiredValue = RequiredPickups.FindChecked(Type);
	int32* CurrentValue = CurrentPickups.Find(Type);
	if (!CurrentValue)
	{
		return;
	}
	*CurrentValue = FMath::Clamp(*CurrentValue + Value, 0, RequiredValue);

	if (DoorWidget)
	{
		DoorWidget->UpdatePickup(Type, *CurrentValue);
	}

	if (*CurrentValue == RequiredValue)
	{
		RequiredPickups.Remove(Type);

		if (RequiredPickups.Num() <= 0)
		{
			OpenDoor();
		}
	}
}

void ADoorBase::InitializeDoor()
{
	InitNameIfNeeded();

	FillPickupMaps();
}

void ADoorBase::InitNameIfNeeded()
{
	if (DoorName == NAME_None)
	{
		DoorName = FName(UKismetSystemLibrary::GetDisplayName(this));
	}
}

void ADoorBase::FillPickupMaps()
{
	if (PickupsFromTheLevel.Num() > 0)
	{
		TArray<APickupBase*> Keys;
		TArray<APickupBase*> Coins;

		for (APickupBase* Pickup : PickupsFromTheLevel)
		{
			switch (Pickup->GetPickupType())
			{
			case EPickupType::Key:
				Keys.Add(Pickup);
				break;
			case EPickupType::Coin:
				Coins.Add(Pickup);
				break;
			default:
				break;
			}

			Pickup->SetDoorToOpen(this);
		}

		if (Keys.Num() > 0)
		{
			RequiredPickups.Add(EPickupType::Key, Keys.Num());
			CurrentPickups.Add(EPickupType::Key, 0);
		}

		if (Coins.Num() > 0)
		{
			RequiredPickups.Add(EPickupType::Coin, Coins.Num());
			CurrentPickups.Add(EPickupType::Coin, 0);
		}
	}

	TArray<AActor*> Pickups;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, APickupBase::StaticClass(), DoorName, Pickups);
	if (Pickups.Num() > 0)
	{
		AddExistingPickups(Pickups);
	}
	else
	{
		RandomisePickups();
	}
	SpawnPickups();

	if (DoorWidget)
	{
		DoorWidget->InitializeWidget(RequiredPickups);
	}
}

void ADoorBase::AddExistingPickups(const TArray<AActor*>& Pickups)
{
	for (AActor* Actor : Pickups)
	{
		APickupBase* Pickup = StaticCast<APickupBase*>(Actor);
		if (Pickup)
		{
			EPickupType Type = Pickup->GetPickupType();
			int32 Value = Pickup->GetValue();

			if (int32* ptr = RequiredPickups.Find(Type))
			{
				*ptr += Value;
			}
			else
			{
				RequiredPickups.Add(Type, Value);
				CurrentPickups.Add(Type, 0);
			}

			Pickup->SetDoorToOpen(this);
		}
	}
}

void ADoorBase::RandomisePickups()
{
	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, APickupSpawner::StaticClass(), DoorName, Spawners);
	if (Spawners.Num() > 0)
	{
		TArray<APickupSpawner*> KeySpawners;
		TArray<APickupSpawner*> CoinSpawners;

		for (AActor* Actor : Spawners)
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

		MaxTheoreticalCoins = CoinSpawners.Num();
		if (MaxRequiredCoins > MaxTheoreticalCoins)
		{
			MaxRequiredCoins = MaxTheoreticalCoins;
		}
		else if (MaxRequiredCoins == 0)
		{
			MaxRequiredCoins = FMath::RandRange(MinRequiredCoins, MaxTheoreticalCoins);
		}

		MaxTheoreticalKeys = KeySpawners.Num();
		if (MaxRequiredKeys > MaxTheoreticalKeys)
		{
			MaxRequiredKeys = MaxTheoreticalKeys;
		}
		else if (MaxRequiredKeys == 0)
		{
			MaxRequiredKeys = FMath::RandRange(MinRequiredKeys, MaxTheoreticalKeys);
		}
	}
	else
	{
		OpenDoor();

		RequiredPickups.Add(EPickupType::Key, 0);
		RequiredPickups.Add(EPickupType::Coin, 0);

		CurrentPickups.Add(EPickupType::Key, 0);
		CurrentPickups.Add(EPickupType::Coin, 0);

		return;
	}

	if (RequiredPickups.IsEmpty())
	{
		if (!RequiredPickups.Find(EPickupType::Key))
		{
			int32 RequiredKeys = FMath::RandRange(MinRequiredKeys, MaxRequiredKeys);
			if (RequiredKeys > 0)
			{
				TTuple<EPickupType, int32> Keys{ EPickupType::Key, RequiredKeys };
				RequiredPickups.Add(Keys);
			}
		}

		if (!RequiredPickups.Find(EPickupType::Coin))
		{
			int32 RequiredCoins = FMath::RandRange(MinRequiredCoins, MaxRequiredCoins);
			if (RequiredCoins > 0)
			{
				TTuple<EPickupType, int32> Coins{ EPickupType::Coin, RequiredCoins };
				RequiredPickups.Add(Coins);
			}
		}
	}

	CurrentPickups.Add(EPickupType::Key, 0);
	CurrentPickups.Add(EPickupType::Coin, 0);
}

void ADoorBase::SpawnPickups()
{
	TArray<AActor*> PickupSpawners;

	UGameplayStatics::GetAllActorsOfClassWithTag(this, APickupSpawner::StaticClass(), DoorName, PickupSpawners);
	if (PickupSpawners.Num() > 0)
	{
		TArray<APickupSpawner*> CastedSpawners;

		TArray<APickupSpawner*> KeySpawners;
		int32 KeysSpawned = 0;

		TArray<APickupSpawner*> CoinSpawners;
		int32 CoinsSpawned = 0;

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

			CastedSpawners.Add(Spawner);
		}

		for (const auto& Pair : RequiredPickups)
		{
			for (int32 i = 0; i < Pair.Value; i++)
			{
				switch (Pair.Key)
				{
				case EPickupType::Key:
					if (KeySpawners.Num() > 0)
					{
						int32 Index = FMath::RandRange(0, KeySpawners.Num() - 1);
						KeySpawners[Index]->SpawnPickup(EPickupType::Key, this);
						KeysSpawned++;
						KeySpawners.RemoveAt(Index);
					}
					break;
				case EPickupType::Coin:
					if (CoinSpawners.Num() > 0)
					{
						int32 Index = FMath::RandRange(0, CoinSpawners.Num() - 1);
						CoinSpawners[Index]->SpawnPickup(EPickupType::Coin, this);
						CoinsSpawned++;
						CoinSpawners.RemoveAt(Index);
					}
					break;
				default:
					break;
				}
			}
		}

		if (KeysSpawned > 0)
		{
			if (int32* ptr = RequiredPickups.Find(EPickupType::Key))
			{
				*ptr += KeysSpawned;
			}
			else
			{
				RequiredPickups.Add(EPickupType::Key, KeysSpawned);
			}
		}

		if (CoinsSpawned > 0)
		{
			if (int32* ptr = RequiredPickups.Find(EPickupType::Coin))
			{
				*ptr += CoinsSpawned;
			}
			else
			{
				RequiredPickups.Add(EPickupType::Coin, CoinsSpawned);
			}
		}
	}
}

void ADoorBase::OpenDoor_Implementation()
{
	//idk if this is better
	//RequiredPickupsWidget->SetVisibility(false);
}
