// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/MenuWidgetBase.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class MIDNIGHTWORKSTEST_API UPauseWidget : public UMenuWidgetBase
{
	GENERATED_BODY()
	
//  Functions

public:
	virtual void NativeConstruct() override;

	virtual void OnStartGameButtonClicked() override;

	UFUNCTION()
	virtual void OnExitToMainMenuButtonClicked();

protected:

private:

//  Variables

public:

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ExitToMainMenuButton;

private:
};
