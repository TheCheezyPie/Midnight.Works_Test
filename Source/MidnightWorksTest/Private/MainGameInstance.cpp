// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"
#include "MoviePlayer.h"

void UMainGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMainGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMainGameInstance::EndLoadingScreen);
}

void UMainGameInstance::BeginLoadingScreen(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreen.MinimumLoadingScreenDisplayTime = 5.0f;

	UUserWidget* LoadingWidget = CreateWidget<UUserWidget>(this, LoadingScreenWidgetClass);
	LoadingScreen.WidgetLoadingScreen = LoadingWidget->TakeWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

void UMainGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
}
