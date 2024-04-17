

#include "Pickups/PickupSpawner.h"
#include "Pickups/PickupBase.h"
#include "Doors/DoorBase.h"
#include "Components/BillboardComponent.h"

APickupSpawner::APickupSpawner()
{
 	PrimaryActorTick.bCanEverTick = true;

	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));
	SetRootComponent(BillboardComponent);
}

void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

APickupBase* APickupSpawner::SpawnPickup(EPickupType PickupType, ADoorBase* PickupOwner)
{
	APickupBase* Pickup = nullptr;

	if (GetWorld())
	{
		TSubclassOf<APickupBase> PickupClass = PickupsClasses.FindChecked(PickupType);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = PickupOwner;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Pickup = GetWorld()->SpawnActor<APickupBase>(PickupClass, GetActorTransform(), SpawnParams);
		if (Pickup)
		{
			Pickup->GetDoorsToOpen().Add(PickupOwner);
		}
	}

	return Pickup;
}

APickupBase* APickupSpawner::SpawnPickupChecked(EPickupType PickupType, ADoorBase* PickupOwner)
{
	if (PickupType == DefaultPickupType)
	{
		return SpawnPickup(PickupType, PickupOwner);
	}

	return nullptr;
}

