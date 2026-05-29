// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "NightSkyGenericPromptWidget.generated.h"

class UNightSkyGenericButton;
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
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	virtual bool NativeOnHandleBackAction() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> PromptText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UNightSkyGenericButton> YesButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UNightSkyGenericButton> NoButton;

	UPROPERTY(BlueprintReadOnly, Category="Default")
	TObjectPtr<UExtendedCommonActivatableWidget> Owner;

	UPROPERTY(BlueprintReadOnly, Category="Default")
	int32 Index = 0;

public:
	UFUNCTION(BlueprintCallable, Category="Default")
	void SetPromptInfo(FText InPromptText, UExtendedCommonActivatableWidget* InPromptOwner, int32 InPromptIndex);
	
	void HandleYesButtonClicked();
	
	void HandleNoButtonClicked();
	
};
