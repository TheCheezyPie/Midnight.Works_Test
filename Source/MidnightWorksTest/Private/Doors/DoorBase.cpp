// Fill out your copyright notice in the Description page of Project Settings.


#include "Doors/DoorBase.h"
#include "GameFramework/GameModes/MainGameMode.h"
#include "Kismet/KismetSystemLibrary.h"

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
		CurrentPickups.Remove(Type);

		if (CurrentPickups.Num() - 1 == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Door %s is open"), *GetName());
			// Open the door
		}
	}
}

void ADoorBase::InitializeDoor()
{
	FillPickupMaps();
	InitNameIfNeeded();
	//SpawnPickups();
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
	int32 RequiredKeys = FMath::RandRange(0, MaxRequiredKeys);
	TTuple<EPickupType, int32> Keys;
	if (RequiredKeys)
	{
		Keys = { EPickupType::Key, RequiredKeys };
	}
	int32 RequiredCoins = FMath::RandRange(1, MaxRequiredCoins);
	TTuple<EPickupType, int32> Coins{ EPickupType::Coin, RequiredCoins };

	RequiredPickups.Add(Keys);
	RequiredPickups.Add(Coins);

	CurrentPickups.Add(EPickupType::Key, 0);
	CurrentPickups.Add(EPickupType::Coin, 0);
}

