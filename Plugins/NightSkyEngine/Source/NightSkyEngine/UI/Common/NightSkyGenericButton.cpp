// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyGenericButton.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"

void UNightSkyGenericButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (DisplayedText)
	{
		DisplayedText->SetText(Text);
	}

	if (ButtonImage)
	{
		ButtonImage->SetBrushFromTexture(Image);
	}
}
