

#include "Pickups/PickupSpawner.h"
#include "Pickups/PickupBase.h"
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

void APickupSpawner::SpawnPickup(EPickupType PickupType)
{
	if (GetWorld())
	{
		TSubclassOf<APickupBase> PickupClass = PickupsClasses.FindChecked(PickupType);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<APickupBase>(PickupClass, GetActorTransform(), SpawnParams);
	}
}

void APickupSpawner::SpawnPickupChecked(EPickupType PickupType)
{
	if (PickupType == DefaultPickupType)
	{
		SpawnPickup(PickupType);
	}
}

