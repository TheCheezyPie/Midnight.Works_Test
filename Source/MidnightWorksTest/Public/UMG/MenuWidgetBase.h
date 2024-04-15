// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class MIDNIGHTWORKSTEST_API UMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
//  Functions

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnStartGameButtonClicked();

	UFUNCTION()
	virtual void OnOptionsButtonClicked();

	UFUNCTION()
	virtual void OnExitGameButtonClicked();

protected:

private:

//  Variables

public:

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> StartGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> OptionsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ExitGameButton;

private:
};
