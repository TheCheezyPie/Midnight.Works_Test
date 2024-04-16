// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"

#include "PickupBase.generated.h"

UCLASS()
class MIDNIGHTWORKSTEST_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

//  Functions

public:
	FORCEINLINE EPickupType GetPickupType() const { return PickupType; }

	FORCEINLINE class ADoorBase* GetDoorToOpen() const { return DoorToOpen; }
	FORCEINLINE void SetDoorToOpen(class ADoorBase* Door) { DoorToOpen = Door; }

protected:
	UFUNCTION()
	void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

//  Variables

public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TObjectPtr<class UCapsuleComponent> CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TObjectPtr<class UStaticMeshComponent> PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TObjectPtr<class UNiagaraComponent> IdleFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TObjectPtr<class UOscillationMovementComponent> OscillationMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TObjectPtr<class UAudioComponent> IdleAudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TObjectPtr<class USoundBase> PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	EPickupType PickupType = EPickupType::Coin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TObjectPtr<class ADoorBase> DoorToOpen;

private:
};
