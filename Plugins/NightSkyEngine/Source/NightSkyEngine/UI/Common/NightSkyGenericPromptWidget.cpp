// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyGenericPromptWidget.h"

#include "CommonTextBlock.h"

void UNightSkyGenericPromptWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	if (UWidget* FocusTarget = GetDesiredFocusTarget())
	{
		FocusTarget->SetFocus();
	}
}

void UNightSkyGenericPromptWidget::SetPromptInfo(FText InPromptText, UExtendedCommonActivatableWidget* InPromptOwner, int32 InPromptIndex)
{
	if (PromptText)
	{
		PromptText->SetText(InPromptText);
	}

	Owner = InPromptOwner;
	Index = InPromptIndex;
}
