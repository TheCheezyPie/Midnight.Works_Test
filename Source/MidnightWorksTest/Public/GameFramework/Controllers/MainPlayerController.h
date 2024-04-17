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
	virtual bool SetPause(bool bPause, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	void TogglePause();

	void AllDoorsOpened();
	void RequiredDoorsOpened();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	void ShowPauseMenu();
	void HidePauseMenu();

//  Variables

public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pause")
	TSubclassOf<class UPauseWidget> PauseMenuWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pause")
	TObjectPtr<UPauseWidget> PauseMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pause")
	TSubclassOf<class UUserWidget> AllDoorsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pause")
	TSubclassOf<class UUserWidget> RequiredDoorsWidgetClass;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> PauseAction;
};
