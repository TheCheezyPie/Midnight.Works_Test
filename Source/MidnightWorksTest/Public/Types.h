#pragma once

#define LOG(Text, ...) UE_LOG(LogTemp, Warning, TEXT(Text), ##__VA_ARGS__)
#define LOG_SCREEN(Text, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(Text), ##__VA_ARGS__))

UENUM(BlueprintType)
enum class EPickupType : uint8
{
	Key,
	Coin,

	MAX = 255
};
