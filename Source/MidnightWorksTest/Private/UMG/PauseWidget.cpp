// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/PauseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ExitToMainMenuButton)
	{
		ExitToMainMenuButton->OnClicked.AddDynamic(this, &UPauseWidget::OnExitToMainMenuButtonClicked);
	}
}

void UPauseWidget::OnStartGameButtonClicked()
{
	Super::OnStartGameButtonClicked();

	GetOwningPlayer()->SetPause(false);
}

void UPauseWidget::OnExitToMainMenuButtonClicked()
{
	UGameplayStatics::OpenLevel(GetOwningPlayer(), "MainMenu");
}
