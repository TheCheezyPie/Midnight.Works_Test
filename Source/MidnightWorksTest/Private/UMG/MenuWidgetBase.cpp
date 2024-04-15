// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/MenuWidgetBase.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton && OptionsButton && ExitGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMenuWidgetBase::OnStartGameButtonClicked);
		OptionsButton->OnClicked.AddDynamic(this, &UMenuWidgetBase::OnOptionsButtonClicked);
		ExitGameButton->OnClicked.AddDynamic(this, &UMenuWidgetBase::OnExitGameButtonClicked);
	}
}

void UMenuWidgetBase::OnStartGameButtonClicked()
{
}

void UMenuWidgetBase::OnOptionsButtonClicked()
{
	// Open Options Menu
}

void UMenuWidgetBase::OnExitGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetOwningPlayer(), GetOwningPlayer(), EQuitPreference::Quit, false);
}
