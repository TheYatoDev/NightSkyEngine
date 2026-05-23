// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyUIBaseWidget.h"
#include "Common/NightSkyGenericPromptWidget.h"

UCommonActivatableWidget* UNightSkyUIBaseWidget::PushMenu(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (!MenuStack || !ActivatableWidgetClass)
	{
		return nullptr;
	}

	return MenuStack->AddWidget<UCommonActivatableWidget>(ActivatableWidgetClass);
}

UNightSkyGenericPromptWidget* UNightSkyUIBaseWidget::PushPrompt(FText InPromptText, UExtendedCommonActivatableWidget* InPromptOwner, int32 InPromptIndex)
{
	if (!PromptStack || !GenericPromptClass)
	{
		return nullptr;
	}

	UNightSkyGenericPromptWidget* PromptWidget = PromptStack->AddWidget<UNightSkyGenericPromptWidget>(GenericPromptClass);

	if (!PromptWidget)
	{
		return nullptr;
	}

	PromptWidget->SetPromptInfo(InPromptText, InPromptOwner, InPromptIndex);
	PromptWidget->OnDeactivated().AddUObject(this, &UNightSkyUIBaseWidget::OnClearPrompt);

	return PromptWidget;
}

void UNightSkyUIBaseWidget::OnClearPrompt()
{
	if (!PromptStack)
	{
		return;
	}

	UCommonActivatableWidget* ActiveWidget = PromptStack->GetActiveWidget();

	if (!ActiveWidget)
	{
		return;
	}

	if (UWidget* FocusTarget = ActiveWidget->GetDesiredFocusTarget())
	{
		FocusTarget->SetFocus();
	}
}

UCommonActivatableWidget* UNightSkyUIBaseWidget::PushModal(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (!PromptStack || !ActivatableWidgetClass)
	{
		return nullptr;
	}

	return PromptStack->AddWidget<UCommonActivatableWidget>(ActivatableWidgetClass);
}
