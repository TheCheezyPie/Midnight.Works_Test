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

void ADoorBase::AddPickup(EPickupType Type)
{
	int32 RequiredValue = RequiredPickups.FindChecked(Type);
	int32* CurrentValue = CurrentPickups.Find(Type);
	if (!CurrentValue)
	{
		return;
	}
	*CurrentValue = FMath::Clamp(*CurrentValue + 1, 0, RequiredValue);

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
	TArray<AActor*> Pickups;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, APickupBase::StaticClass(), DoorName, Pickups);

	if (bRandomisePickupsAbovePreset || (Pickups.Num() == 0 && PickupsFromLevel.Num() == 0))
	{
		RandomisePickups();
	}
	SpawnPickups();

	if (PickupsFromLevel.Num() > 0)
	{
		AccountForPickupsFromLevel();
	}

	if (Pickups.Num() > 0)
	{
		AddExistingPickups(Pickups);
	}

	auto RequiredPickupsCopy = RequiredPickups;
	for (auto& Pair : RequiredPickupsCopy)
	{
		if (Pair.Value == 0)
		{
			RequiredPickups.Remove(Pair.Key);
			CurrentPickups.Remove(Pair.Key);
		}
	}

	CurrentPickups.Add(EPickupType::Key, 0);
	CurrentPickups.Add(EPickupType::Coin, 0);

	if (RequiredPickups.Num() == 0)
	{
		bIsEnabled = false;

		if (DoorWidget)
		{
			DoorWidget->InitializeWidget();
		}

		OpenSound = nullptr;
		OpenDoor();
	}
	else
	{
		if (DoorWidget)
		{
			DoorWidget->InitializeWidget(RequiredPickups);
		}
	}
}

void ADoorBase::AccountForPickupsFromLevel()
{
	int32 KeysSpawned = 0;
	int32 CoinsSpawned = 0;

	for (APickupBase* Pickup : PickupsFromLevel)
	{
		if (Pickup && !Pickup->GetDoorsToOpen().Contains(this))
		{
			switch (Pickup->GetPickupType())
			{
			case EPickupType::Key:
				KeysSpawned++;
				break;
			case EPickupType::Coin:
				CoinsSpawned++;
				break;
			default:
				break;
			}

			Pickup->GetDoorsToOpen().Add(this);
		}
	}

	if (KeysSpawned > 0)
	{
		MapAddChecked(EPickupType::Key, false, KeysSpawned);
	}

	if (CoinsSpawned > 0)
	{
		MapAddChecked(EPickupType::Coin, false, CoinsSpawned);
	}
}

void ADoorBase::AddExistingPickups(const TArray<AActor*>& Pickups)
{
	for (AActor* Actor : Pickups)
	{
		APickupBase* Pickup = StaticCast<APickupBase*>(Actor);
		if (Pickup && !Pickup->GetDoorsToOpen().Contains(this))
		{
			EPickupType Type = Pickup->GetPickupType();

			MapAddChecked(Type, false);

			Pickup->GetDoorsToOpen().Add(this);
		}
	}
}

void ADoorBase::RandomisePickups()
{
	int32 RequiredKeys = FMath::RandRange(MinRequiredKeys, MaxRequiredKeys);
	if (RequiredKeys > 0)
	{
		MapAddChecked(EPickupType::Key, false, RequiredKeys);
	}

	int32 RequiredCoins = FMath::RandRange(MinRequiredCoins, MaxRequiredCoins);
	if (RequiredCoins > 0)
	{
		MapAddChecked(EPickupType::Coin, false, RequiredCoins);
	}
}

void ADoorBase::SpawnPickups()
{
	int32 KeysToSpawn = 0;
	if (int32* ptr = RequiredPickups.Find(EPickupType::Key))
	{
		KeysToSpawn = *ptr;
	}
	else
	{
		RequiredPickups.Add(EPickupType::Key, 0);
	}

	int32 CoinsToSpawn = 0;
	if (int32* ptr = RequiredPickups.Find(EPickupType::Coin))
	{
		CoinsToSpawn = *ptr;
	}
	else
	{
		RequiredPickups.Add(EPickupType::Coin, 0);
	}

	int32 KeysSpawned = 0;
	int32 CoinsSpawned = 0;

	TArray<AActor*> PickupSpawners;

	UGameplayStatics::GetAllActorsOfClassWithTag(this, APickupSpawner::StaticClass(), DoorName, PickupSpawners);
	if (PickupSpawners.Num() > 0)
	{
		TArray<APickupSpawner*> AllSpawners;
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

			AllSpawners.Add(Spawner);
		}

		for (const auto& Pair : RequiredPickups)
		{
			for (int32 i = 0; i < Pair.Value; i++)
			{
				switch (Pair.Key)
				{
				case EPickupType::Key:
					if (KeySpawners.Num() > 0 && KeysToSpawn > 0)
					{
						int32 Index = FMath::RandRange(0, KeySpawners.Num() - 1);
						APickupBase* Pickup = KeySpawners[Index]->SpawnPickupChecked(EPickupType::Key, this);
						if (Pickup)
						{
							KeysSpawned++;
						}
						KeySpawners.RemoveAt(Index);
					}
					break;
				case EPickupType::Coin:
					if (CoinSpawners.Num() > 0 && CoinsToSpawn > 0)
					{
						int32 Index = FMath::RandRange(0, CoinSpawners.Num() - 1);
						APickupBase* Pickup = CoinSpawners[Index]->SpawnPickupChecked(EPickupType::Coin, this);
						if (Pickup)
						{
							CoinsSpawned++;
						}
						CoinSpawners.RemoveAt(Index);
					}
					break;
				default:
					break;
				}
			}
		}
	}

	if (KeysToSpawn > 0)
	{
		if (int32* ptr = RequiredPickups.Find(EPickupType::Key))
		{
			if (KeysSpawned < KeysToSpawn)
			{
				*ptr -= (KeysToSpawn - KeysSpawned);
			}
		}
		else
		{
			RequiredPickups.Add(EPickupType::Key, KeysSpawned);
		}
	}

	if (CoinsToSpawn > 0)
	{
		if (int32* ptr = RequiredPickups.Find(EPickupType::Coin))
		{
			if (CoinsSpawned < CoinsToSpawn)
			{
				*ptr -= (CoinsToSpawn - CoinsSpawned);
			}
		}
		else
		{
			RequiredPickups.Add(EPickupType::Coin, CoinsSpawned);
		}
	}
}

bool ADoorBase::MapAddChecked(EPickupType Type, bool bIsCurrentMap, int32 Value)
{
	TMap<EPickupType, int32>* Map = bIsCurrentMap ? &CurrentPickups : &RequiredPickups;
	int32* ptr = Map->Find(Type);
	if (ptr)
	{
		*ptr += Value;
	}
	else
	{
		Map->Add(Type, Value);
	}
	return (bool)ptr;
}

void ADoorBase::OpenDoor_Implementation()
{
	if (OpenSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
	}

	AMainGameMode* GM = GetWorld()->GetAuthGameMode<AMainGameMode>();
	if (GM && bIsEnabled)
	{
		GM->DoorOpened(this);
	}

	//idk if this is better
	//RequiredPickupsWidget->SetVisibility(false);
}
