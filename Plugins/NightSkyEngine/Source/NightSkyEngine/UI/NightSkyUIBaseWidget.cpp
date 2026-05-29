// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyUIBaseWidget.h"
#include "Common/NightSkyGenericPromptWidget.h"

void UNightSkyUIBaseWidget::PushMenu(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (!MenuStack || !ActivatableWidgetClass)
	{
		return;
	}

	MenuStack->AddWidget<UCommonActivatableWidget>(ActivatableWidgetClass);
}

void UNightSkyUIBaseWidget::PushPrompt(FText InPromptText, UExtendedCommonActivatableWidget* InPromptOwner, int32 InPromptIndex)
{
	if (!PromptStack || !GenericPromptClass)
	{
		return;
	}

	UNightSkyGenericPromptWidget* PromptWidget = PromptStack->AddWidget<UNightSkyGenericPromptWidget>(GenericPromptClass);

	if (!PromptWidget)
	{
		return;
	}

	PromptWidget->SetPromptInfo(InPromptText, InPromptOwner, InPromptIndex);
	PromptWidget->OnDeactivated().AddUObject(this, &UNightSkyUIBaseWidget::OnClearPrompt);
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

void UNightSkyUIBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	bDisplayInActionBar = true;
}

void UNightSkyUIBaseWidget::PushModal(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (!PromptStack || !ActivatableWidgetClass)
	{
		return;
	}

	PromptStack->AddWidget<UCommonActivatableWidget>(ActivatableWidgetClass);
}
