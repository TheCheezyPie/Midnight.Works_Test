// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/MenuWidgetBase.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MIDNIGHTWORKSTEST_API UMainMenuWidget : public UMenuWidgetBase
{
	GENERATED_BODY()
	
//  Functions

public:
	virtual void OnStartGameButtonClicked() override;

protected:

private:

//  Variables

public:

protected:

private:
};
