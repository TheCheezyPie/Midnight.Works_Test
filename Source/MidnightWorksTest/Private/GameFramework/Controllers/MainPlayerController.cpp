// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Controllers/MainPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "UMG/PauseWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (PauseMenuWidgetClass)
	{
		PauseMenuWidget = CreateWidget<UPauseWidget>(this, PauseMenuWidgetClass);
		if (PauseMenuWidget)
		{
			PauseMenuWidget->AddToViewport();
			PauseMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AMainPlayerController::TogglePause);
	}
}

bool AMainPlayerController::SetPause(bool bPause, FCanUnpause CanUnpauseDelegate)
{
	bool bResult = Super::SetPause(bPause, CanUnpauseDelegate);


	return bResult;
}

void AMainPlayerController::TogglePause()
{
	bool bNewPause = !IsPaused();

	SetPause(bNewPause);

	if (bNewPause)
	{
		ShowPauseMenu();

		FInputModeGameAndUI InputMode;
		SetInputMode(InputMode);

		SetShowMouseCursor(true);
	}
	else
	{
		HidePauseMenu();

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);

		SetShowMouseCursor(false);
	}
}

void AMainPlayerController::AllDoorsOpened()
{
	if (AllDoorsWidgetClass)
	{
		UUserWidget* Widget = CreateWidget(this, AllDoorsWidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}

void AMainPlayerController::RequiredDoorsOpened()
{
	if (RequiredDoorsWidgetClass)
	{
		UUserWidget* Widget = CreateWidget(this, RequiredDoorsWidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}

void AMainPlayerController::AdditionalDoorsOpened()
{
	if (AdditionalDoorsWidgetClass)
	{
		UUserWidget* Widget = CreateWidget(this, AdditionalDoorsWidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}

void AMainPlayerController::ShowPauseMenu()
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void AMainPlayerController::HidePauseMenu()
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

