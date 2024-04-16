

#include "Components/OscillationMovementComponent.h"

UOscillationMovementComponent::UOscillationMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UOscillationMovementComponent::BeginPlay()
{
	Super::BeginPlay();


}


void UOscillationMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner() && bShouldMove)
	{
		float Trig = 0;
		if (bUseCos)
		{
			Trig = FMath::Cos(GetOwner()->GetGameTimeSinceCreation() * MovementSpeed);
		}
		else
		{
			Trig = FMath::Sin(GetOwner()->GetGameTimeSinceCreation() * MovementSpeed);
		}
		GetOwner()->AddActorLocalOffset(FVector(0.f, 0.f, Trig * Amplitude));
		GetOwner()->AddActorLocalRotation(RotationSpeed * DeltaTime);
	}
}

void UOscillationMovementComponent::Stop()
{
	bShouldMove = false;
}

void UOscillationMovementComponent::Resume()
{
	bShouldMove = true;
}

