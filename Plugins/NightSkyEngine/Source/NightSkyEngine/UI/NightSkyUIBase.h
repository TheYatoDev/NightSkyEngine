// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Components/Overlay.h"
#include "Input/CommonBoundActionBar.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "NightSkyUIBase.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyUIBase : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UOverlay> Overlay;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> MenuStack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> PromptStack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonBoundActionBar> ActionBar;
	
};
