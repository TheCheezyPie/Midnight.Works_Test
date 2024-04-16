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
	FORCEINLINE FName GetDoorName() const { return DoorName; }
	FORCEINLINE bool IsRequired() const { return bIsRequired; }

	void InitializeDoor();
	void AddPickup(EPickupType Type);

protected:
	void InitNameIfNeeded();
	void FillPickupMaps();
	void AccountForPickupsFromLevel();
	void AddExistingPickups(const TArray<AActor*>& Pickups);
	void RandomisePickups();
	void SpawnPickups();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenDoor();

private:
	// @return true if the Value was added, false if it was created
	bool MapAddChecked(EPickupType Type, bool bIsCurrentMap, int32 Value = 1);

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
	TObjectPtr<class UArrowComponent> FrontArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<class UWidgetComponent> RequiredPickupsWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<class UDoorWidget> DoorWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	TObjectPtr<class USoundBase> OpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	FName DoorName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	TMap<EPickupType, int32> RequiredPickups;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Door")
	TMap<EPickupType, int32> CurrentPickups;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	bool bIsRequired = true;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Door|Pickups")
	TArray<class APickupBase*> PickupsFromLevel;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Door|Pickups")
	bool bRandomisePickupsAbovePreset = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door|Pickups|Keys")
	int32 MinRequiredKeys = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door|Pickups|Keys")
	int32 MaxRequiredKeys = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door|Pickups|Coins")
	int32 MinRequiredCoins = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door|Pickups|Coins")
	int32 MaxRequiredCoins = 5;

private:
};
