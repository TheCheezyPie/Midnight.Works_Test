
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"

#include "PickupSpawner.generated.h"

UCLASS()
class MIDNIGHTWORKSTEST_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
//  Functions

public:
	void SpawnPickup(EPickupType PickupType);
	void SpawnPickupChecked(EPickupType PickupType);

	FORCEINLINE EPickupType GetPickupType() const { return DefaultPickupType; }

protected:

private:

//  Variables

public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBillboardComponent> BillboardComponent;

	UPROPERTY(EditAnywhere, Category = "Pickups")
	EPickupType DefaultPickupType;

	UPROPERTY(EditAnywhere, Category = "Pickups")
	TMap<EPickupType, TSubclassOf<class APickupBase>> PickupsClasses;

private:
};