// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyStageSelectButton.h"
#include "NightSkyStageSelectGrid.h"
#include "Components/Image.h"
#include "NightSkyEngine/Data/PrimaryStageData.h"

void UNightSkyStageSelectButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	//OnHovered().AddUObject(this, &UNightSkyStageSelectButton::HandleHovered);
	//OnClicked().AddUObject(this, &UNightSkyStageSelectButton::HandleClicked);
	
	if (!StageData) return;

	UTexture2D* Icon = StageData->StageSelectIcon;
	if (!Icon) return;

	if (ButtonImage)
	{
		ButtonImage->SetBrushFromTexture(Icon);
	}
}

void UNightSkyStageSelectButton::NativeOnHovered()
{
	Super::NativeOnHovered();
	
	UE_LOG(LogTemp, Warning, TEXT("NativeOnHovered - Owner=%s, StageData=%s"),
		Owner ? *Owner->GetName() : TEXT("null"),
		StageData ? *StageData->GetName() : TEXT("null"));
	
	if (Owner && StageData)
	{
		Owner->OnStageHovered(StageData->StageFriendlyName);
	}
}

void UNightSkyStageSelectButton::NativeOnClicked()
{
	Super::NativeOnClicked();
	
	UE_LOG(LogTemp, Warning, TEXT("NativeOnClicked - Owner=%s, StageData=%s"),
		Owner ? *Owner->GetName() : TEXT("null"),
		StageData ? *StageData->GetName() : TEXT("null"));
	
	if (Owner)
	{
		Owner->OnStageSelected(StageData);
	}
}

