// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/MenuWidgetBase.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton && ExitGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMenuWidgetBase::OnStartGameButtonClicked);
		ExitGameButton->OnClicked.AddDynamic(this, &UMenuWidgetBase::OnExitGameButtonClicked);
	}
}

void UMenuWidgetBase::OnStartGameButtonClicked()
{
}

void UMenuWidgetBase::OnExitGameButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetOwningPlayer(), GetOwningPlayer(), EQuitPreference::Quit, false);
}
