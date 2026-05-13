// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyCSelectButton.h"

#include "NightSkyCharaSelectGrid.h"
#include "NightSkyEngine/Data/PrimaryCharaData.h"

void UNightSkyCSelectButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!ButtonImage || !CharaData)
	{
		return;
	}
	
	ButtonImage->SetBrushFromTexture(CharaData->CharaSelectIcon, false);
}

void UNightSkyCSelectButton::NativeOnHovered()
{
	Super::NativeOnHovered();
	
	UE_LOG(LogTemp, Warning, TEXT("Hovered button: %s | Grid: %s | CharaData: %s"),
		*GetNameSafe(this),
		*GetNameSafe(OwningGrid),
		*GetNameSafe(CharaData));
	
	if (OwningGrid && CharaData)
	{
		OwningGrid->OnCharaHovered(CharaData->CharaFriendlyName);
	}
}

void UNightSkyCSelectButton::NativeOnClicked()
{
	Super::NativeOnClicked();
	
	if (OwningGrid && CharaData)
	{
		OwningGrid->OnCharaSelected(CharaData);
	}
}

void UNightSkyCSelectButton::InitButton(UPrimaryCharaData* InCharaData, UNightSkyCharaSelectGrid* InOwningGrid)
{
	CharaData = InCharaData;
	OwningGrid = InOwningGrid;

	if (ButtonImage && CharaData)
	{
		ButtonImage->SetBrushFromTexture(CharaData->CharaSelectIcon, false);
	}
}

