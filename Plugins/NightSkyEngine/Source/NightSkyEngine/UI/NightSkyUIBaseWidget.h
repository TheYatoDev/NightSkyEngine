// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "ExtendedCommonActivatableWidget.h"
#include "Common/NightSkyGenericPromptWidget.h"
#include "Components/Overlay.h"
#include "Input/CommonBoundActionBar.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "NightSkyUIBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyUIBaseWidget : public UCommonActivatableWidget
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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default")
	TSubclassOf<UNightSkyGenericPromptWidget> GenericPromptClass;
	
	virtual void NativeConstruct() override;
	
public:
	UFUNCTION(BlueprintCallable, Category="Default")
	void PushModal(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	
	UFUNCTION(BlueprintCallable, Category="Default")
	void PushMenu(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	
	UFUNCTION(BlueprintCallable, Category="Default")
	void PushPrompt(FText InPromptText, UExtendedCommonActivatableWidget* InPromptOwner, int32 InPromptIndex);
	
	UFUNCTION()
	void OnClearPrompt();
	
};
