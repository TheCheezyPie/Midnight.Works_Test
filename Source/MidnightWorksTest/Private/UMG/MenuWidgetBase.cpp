// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/MenuWidgetBase.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton && ExitGameButton)
	{
		StartGameButton->OnReleased.AddDynamic(this, &UMenuWidgetBase::OnStartGameButtonClicked);
		ExitGameButton->OnReleased.AddDynamic(this, &UMenuWidgetBase::OnExitGameButtonClicked);
	}
}

void UMenuWidgetBase::OnStartGameButtonClicked()
{
}

void UMenuWidgetBase::OnExitGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetOwningPlayer(), GetOwningPlayer(), EQuitPreference::Quit, false);
}
