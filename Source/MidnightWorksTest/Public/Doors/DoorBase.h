// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"

#include "DoorBase.generated.h"

UCLASS()
class MIDNIGHTWORKSTEST_API ADoorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

//  Functions

public:
	void AddPickup(EPickupType Type, int32 Value);

protected:
	void InitializeDoor();
	void InitNameIfNeeded();
	void FillPickupMaps();

private:

//  Variables

public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> FrameMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	FName DoorName = NAME_None;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
	TMap<EPickupType, int32> RequiredPickups;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
	TMap<EPickupType, int32> CurrentPickups;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	int32 MaxRequiredKeys = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	int32 MaxRequiredCoins = 5;

private:
};
