// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MIDNIGHTWORKSTEST_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

//  Functions

public:
	void TogglePauseMenu();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:

//  Variables

public:

protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseAction;
};
