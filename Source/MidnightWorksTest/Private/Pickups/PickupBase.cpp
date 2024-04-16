

#include "Pickups/PickupBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Doors/DoorBase.h"
#include "Components/OscillationMovementComponent.h"

APickupBase::APickupBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(CollisionComponent);

	PickupFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupFX"));
	PickupFX->SetupAttachment(PickupMesh);

	OscillationMovementComponent = CreateDefaultSubobject<UOscillationMovementComponent>(TEXT("OscillationMovementComponent"));
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnCollisionBeginOverlap);
}

void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupBase::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		if (DoorToOpen)
		{
			DoorToOpen->AddPickup(PickupType);
			Destroy();
		}
	}
}

