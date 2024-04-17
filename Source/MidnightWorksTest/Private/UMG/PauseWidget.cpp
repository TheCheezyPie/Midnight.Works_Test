// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/PauseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "GameFramework/Controllers/MainPlayerController.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ExitToMainMenuButton)
	{
		ExitToMainMenuButton->OnReleased.AddDynamic(this, &UPauseWidget::OnExitToMainMenuButtonClicked);
	}
}

void UPauseWidget::OnStartGameButtonClicked()
{
	Super::OnStartGameButtonClicked();

	GetOwningPlayer<AMainPlayerController>()->TogglePause();
}

void UPauseWidget::OnExitToMainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(GetOwningPlayer(), "MainMenu");
}
