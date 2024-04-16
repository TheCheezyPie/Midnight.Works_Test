// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/DoorWidget.h"
#include "Components/TextBlock.h"

void UDoorWidget::InitializeWidget(const TMap<EPickupType, int32>& RequiredPickups)
{
	if (const int32* ptr_RequiredKeys = RequiredPickups.Find(EPickupType::Key))
	{
		RequiredKeys = *ptr_RequiredKeys;
		CurrentKeys = 0;
		RequiredKeysText->SetText(FText::FromString(FString::FromInt(RequiredKeys)));
		CurrentKeysText->SetText(FText::FromString(FString::FromInt(0)));
	}
	else
	{
		HideTypeText(EPickupType::Key);
	}

	if (const int32* ptr_RequiredCoins = RequiredPickups.Find(EPickupType::Coin))
	{
		RequiredCoins = *ptr_RequiredCoins;
		CurrentCoins = 0;
		RequiredCoinsText->SetText(FText::FromString(FString::FromInt(RequiredCoins)));
		CurrentCoinsText->SetText(FText::FromString(FString::FromInt(0)));
	}
	else
	{
		HideTypeText(EPickupType::Coin);
	}
}

void UDoorWidget::UpdatePickup(EPickupType Type, int32 NewValue)
{
	switch (Type)
	{
	case EPickupType::Key:
		CurrentKeysText->SetText(FText::FromString(FString::FromInt(NewValue)));
		CurrentKeys = NewValue;
		if (CurrentKeys == RequiredKeys)
		{
			PickupCompleted(Type);
		}
		break;
	case EPickupType::Coin:
		CurrentCoinsText->SetText(FText::FromString(FString::FromInt(NewValue)));
		CurrentCoins = NewValue;
		if (CurrentCoins == RequiredCoins)
		{
			PickupCompleted(Type);
		}
		break;
	}
}
