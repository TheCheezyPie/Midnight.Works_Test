// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::OnStartGameButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainLevel");
}
