// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyCharaSelectGrid.h"

#include "Components/CanvasPanel.h"
#include "Components/Overlay.h"
#include "Components/WrapBox.h"

#include "CommonBorder.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "NightSkyCSelectButton.h"
#include "VectorTypes.h"
#include "NightSkyEngine/Data/PrimaryCharaData.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"


void UNightSkyCharaSelectGrid::NativeConstruct()
{
	Super::NativeConstruct();
	SetCharNum();
	GameState = Cast<ANightSkyCharaSelectGameState>(GetWorld()->GetGameState());
	GameState->GatherCharaData();
	CharBox->ClearChildren();
	
	PopulateButtons();
}

void UNightSkyCharaSelectGrid::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (GameState && GameState->P1Charas.Num() == 0)
	{
		bIsP1 = true;
	}
}

void UNightSkyCharaSelectGrid::PopulateButtons()
{
	if (!GameState || !CharBox || !ButtonClass)
	{
		return;
	}

	CharBox->ClearChildren();
	Buttons.Empty();

	for (UPrimaryCharaData* CharaData : GameState->CharaDatas)
	{
		if (!CharaData)
		{
			continue;
		}

		UNightSkyCSelectButton* CSelectButton =
			CreateWidget<UNightSkyCSelectButton>(GetOwningPlayer(), ButtonClass);

		if (!CSelectButton)
		{
			continue;
		}

		CSelectButton->bIsFocusable = true;
		CSelectButton->SetIsSelectable(true);
		CSelectButton->SetIsInteractionEnabled(true);
		CSelectButton->InitButton(CharaData, this);

		CharBox->AddChild(CSelectButton);
		Buttons.Add(CSelectButton);

		UE_LOG(LogTemp, Warning, TEXT("Spawned Button Class: %s"),
			*GetNameSafe(CSelectButton->GetClass()));
	}
}

UWidget* UNightSkyCharaSelectGrid::NativeGetDesiredFocusTarget() const
{
	if (Buttons.Num() > 0 && Buttons[0])
	{
		return Buttons[0];
	}

	if (CharBox && CharBox->GetChildrenCount() > 0)
	{
		return CharBox->GetChildAt(0);
	}

	return Super::NativeGetDesiredFocusTarget();
}

void UNightSkyCharaSelectGrid::SetCharNum()
{
	UGameInstance* GI = GetGameInstance();
	if (!GI)
	{
		return;
	}

	UNightSkyGameInstance* NightSkyGI = Cast<UNightSkyGameInstance>(GI);
	if (!NightSkyGI)
	{
		return;
	}

	CharNumP1 = NightSkyGI->TeamSizeP1;
	CharNumP2 = NightSkyGI->TeamSizeP2;
}

void UNightSkyCharaSelectGrid::OnCharaHovered(FText Name)
{
	if (bIsP1)
	{
		if (SelectedP1)
		{
			SelectedP1->SetText(Name);
		}
	}
	else
	{
		if (SelectedP2)
		{
			SelectedP2->SetText(Name);
		}
	}
}

void UNightSkyCharaSelectGrid::OnCharaSelected(UPrimaryCharaData* Player)
{
	
}

