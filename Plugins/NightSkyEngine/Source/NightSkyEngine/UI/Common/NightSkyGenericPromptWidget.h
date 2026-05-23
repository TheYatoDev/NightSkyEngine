// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "NightSkyGenericPromptWidget.generated.h"

class UNightSkyUIBaseWidget;
class UExtendedCommonActivatableWidget;
class UCommonTextBlock;
/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyGenericPromptWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnActivated() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> PromptText;

	UPROPERTY(BlueprintReadOnly, Category="Prompt")
	TObjectPtr<UExtendedCommonActivatableWidget> Owner;

	UPROPERTY(BlueprintReadOnly, Category="Prompt")
	int32 Index = 0;

public:
	UFUNCTION(BlueprintCallable, Category="Prompt")
	void SetPromptInfo(FText InPromptText, UExtendedCommonActivatableWidget* InPromptOwner, int32 InPromptIndex);
	
};
