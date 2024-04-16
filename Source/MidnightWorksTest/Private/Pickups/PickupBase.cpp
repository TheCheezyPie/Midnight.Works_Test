

#include "Pickups/PickupBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Doors/DoorBase.h"
#include "Components/OscillationMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

APickupBase::APickupBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(CollisionComponent);

	IdleFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupFX"));
	IdleFX->SetupAttachment(PickupMesh);

	IdleAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("IdleAudioComponent"));
	IdleAudioComponent->bAutoActivate = false;

	OscillationMovementComponent = CreateDefaultSubobject<UOscillationMovementComponent>(TEXT("OscillationMovementComponent"));
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnCollisionBeginOverlap);
	IdleAudioComponent->Activate();
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
			if (PickupSound)
			{
				UGameplayStatics::SpawnSoundAttached(PickupSound, OtherActor->GetRootComponent());
			}
			Destroy();
		}
	}
}

