// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyWardrobeSelect.h"
#include "CommonNumericTextBlock.h"
#include "NightSkyCharaSelectGrid.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "NightSkyEngine/UI/Common/NightSkyGenericButton.h"

void UNightSkyWardrobeSelect::NativeConstruct()
{
	Super::NativeConstruct();
    
	if (Confirm)
	{
		Confirm->OnClicked().Clear();
		Confirm->OnClicked().AddUObject(
			this,
			&UNightSkyWardrobeSelect::HandleConfirmClicked
		);
	}
    
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(
		this, FoundWidgets, UNightSkyCharaSelectGrid::StaticClass(), false);

	if (FoundWidgets.Num() <= 0)
	{
		return;
	}

	Owner = Cast<UNightSkyCharaSelectGrid>(FoundWidgets[0]);

	if (!Owner)
	{
		return;
	}

	bIsP1 = Owner->bIsP1;
}

UWidget* UNightSkyWardrobeSelect::NativeGetDesiredFocusTarget() const
{
	return Confirm;
}

bool UNightSkyWardrobeSelect::NativeOnHandleBackAction()
{
	if (Owner)
	{
		Owner->Back();
	}
	DeactivateWidget();
	return true;
}

void UNightSkyWardrobeSelect::HandleConfirmClicked()
{
	if (Owner && Owner->GameState && ColorIndex)
	{
		const int32 InColor = FMath::TruncToInt(ColorIndex->GetTargetValue());

		Owner->GameState->AddColorIndex(
			InColor,
			bIsP1
		);
		
		DeactivateWidget();
		Owner->OnCharaConfirm();
	}
}
