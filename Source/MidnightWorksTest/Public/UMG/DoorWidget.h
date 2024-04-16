// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types.h"

#include "DoorWidget.generated.h"

/**
 * 
 */
UCLASS()
class MIDNIGHTWORKSTEST_API UDoorWidget : public UUserWidget
{
	GENERATED_BODY()

//  Functions

public:
	// For when the door is opened by default
	void InitializeWidget();
	void InitializeWidget(const TMap<EPickupType, int32>& RequiredPickups);
	void UpdatePickup(EPickupType Type, int32 NewValue);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PickupCompleted(EPickupType Type);

	UFUNCTION(BlueprintImplementableEvent)
	void HideTypeText(EPickupType Type);

private:

//  Variables

public:

protected:
	int32 RequiredKeys, CurrentKeys;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> CurrentKeysText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<class UTextBlock> RequiredKeysText;

	int32 RequiredCoins, CurrentCoins;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> CurrentCoinsText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<class UTextBlock> RequiredCoinsText;
private:
	
};
