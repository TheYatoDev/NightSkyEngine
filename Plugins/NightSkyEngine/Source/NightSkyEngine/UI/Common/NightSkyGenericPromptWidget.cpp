// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyGenericPromptWidget.h"
#include "CommonTextBlock.h"
#include "NightSkyGenericButton.h"
#include "NightSkyEngine/UI/ExtendedCommonActivatableWidget.h"

void UNightSkyGenericPromptWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	if (UWidget* FocusTarget = GetDesiredFocusTarget())
	{
		FocusTarget->SetFocus();
	}
}

void UNightSkyGenericPromptWidget::NativeConstruct()
{
	if (YesButton)
	{
		YesButton->OnClicked().AddUObject(
			this,
			&UNightSkyGenericPromptWidget::HandleYesButtonClicked
		);
	}
	
	if (NoButton)
	{
		NoButton->OnClicked().AddUObject(
			this,
			&UNightSkyGenericPromptWidget::HandleNoButtonClicked
		);
	}
}

UWidget* UNightSkyGenericPromptWidget::NativeGetDesiredFocusTarget() const
{
	return YesButton;
}

bool UNightSkyGenericPromptWidget::NativeOnHandleBackAction()
{
	DeactivateWidget();
	return true;
}

FReply UNightSkyGenericPromptWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (UWidget* FocusTarget = NativeGetDesiredFocusTarget())
	{
		FocusTarget->SetFocus();
	}

	return FReply::Handled();
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

void UNightSkyGenericPromptWidget::HandleYesButtonClicked()
{
	if (Owner)
	{
		Owner->OnPromptConfirm(Index);
	}
}

void UNightSkyGenericPromptWidget::HandleNoButtonClicked()
{
	DeactivateWidget();
}
