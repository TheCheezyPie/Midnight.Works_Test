// Fill out your copyright notice in the Description page of Project Settings.


#include "Doors/DoorBase.h"
#include "GameFramework/GameModes/MainGameMode.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/PickupBase.h"

ADoorBase::ADoorBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetupAttachment(GetRootComponent());

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(FrameMesh);
}

void ADoorBase::BeginPlay()
{
	Super::BeginPlay();

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

	if (*CurrentValue == RequiredValue)
	{
		RequiredPickups.Remove(Type);

		if (RequiredPickups.Num() <= 0)
		{
			LOG_SCREEN("Door %s is open", *DoorName.ToString());
			// Open the door
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
		DoorName = GetFName();
	}
}

void ADoorBase::FillPickupMaps()
{
	TArray<AActor*> Pickups;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, APickupBase::StaticClass(), DoorName, Pickups);
	if (Pickups.Num() > 0)
	{
		AddExistingPickups(Pickups);
	}
	else
	{
		RandomisePickups();
		SpawnPickups();
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
			RequiredPickups.Add(Type, Value);
			CurrentPickups.Add(Type, 0);
		}
	}
}

void ADoorBase::RandomisePickups()
{
	int32 RequiredKeys = FMath::RandRange(MinRequiredKeys, MaxRequiredKeys);
	if (RequiredKeys > 0)
	{
		TTuple<EPickupType, int32> Keys{ EPickupType::Key, RequiredKeys };
		RequiredPickups.Add(Keys);
		CurrentPickups.Add(EPickupType::Key, 0);
	}

	int32 RequiredCoins = FMath::RandRange(MinRequiredCoins, MaxRequiredCoins);
	if (RequiredCoins > 0)
	{
		TTuple<EPickupType, int32> Coins{ EPickupType::Coin, RequiredCoins };
		RequiredPickups.Add(Coins);
		CurrentPickups.Add(EPickupType::Coin, 0);
	}
}

void ADoorBase::SpawnPickups()
{
	AMainGameMode* GameMode = GetWorld()->GetAuthGameMode<AMainGameMode>();
	if (GameMode)
	{
		GameMode->SpawnPickups(DoorName, RequiredPickups);
	}
}

