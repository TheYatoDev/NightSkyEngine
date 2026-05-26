// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyCharaSelectGrid.h"
#include "Components/CanvasPanel.h"
//#include "Components/Overlay.h"
#include "Components/WrapBox.h"
//#include "CommonBorder.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "NightSkyCSelectButton.h"
//#include "VectorTypes.h"
#include "NightSkyCharaPlayerSelectController.h"
#include "Kismet/GameplayStatics.h"
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

void UNightSkyCharaSelectGrid::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	SetDesiredFocusWidget(GetDesiredFocusTarget());
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
		
		CSelectButton->SetIsSelectable(true);
		CSelectButton->SetIsInteractionEnabled(true);
		CSelectButton->InitButton(CharaData, this);

		CharBox->AddChild(CSelectButton);
		Buttons.Add(CSelectButton);

		UE_LOG(LogTemp, Warning, TEXT("Spawned Button Class: %s"), *GetNameSafe(CSelectButton->GetClass()));
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
	if (!Player)
	{
		return;
	}

	UNightSkyGameInstance* NightSkyGI = Cast<UNightSkyGameInstance>(GetGameInstance());

	if (!NightSkyGI)
	{
		return;
	}

	int32 Index = INDEX_NONE;

	if (bIsP1)
	{
		const int32 ExistingIndex =
			NightSkyGI->BattleData.PlayerListP1.IndexOfByPredicate(
				[Player](const TSoftObjectPtr<UPrimaryCharaData>& Entry)
				{
					return Entry.Get() == Player;
				}
			);

		if (CharNumP1 > ExistingIndex || ExistingIndex == INDEX_NONE)
		{
			Index = CharNumP1;
		}
	}
	else
	{
		for (int32 ArrayIndex = 0; ArrayIndex < NightSkyGI->BattleData.PlayerListP1.Num(); ++ArrayIndex)
		{
			const TSoftObjectPtr<UPrimaryCharaData>& Entry =
				NightSkyGI->BattleData.PlayerListP1[ArrayIndex];

			if (Entry.Get() == Player && ArrayIndex < CharNumP2)
			{
				Index = CharNumP2;
				break;
			}
		}
	}

	if (Index == INDEX_NONE)
	{
		return;
	}
}

void UNightSkyCharaSelectGrid::OnCharaConfirm()
{
	const bool bP1Complete =
		GameState && GameState->P1Charas.Num() >= CharNumP1;

	if (bP1Complete && !bIsP1)
	{
		bIsP1 = false;

		UNightSkyGameInstance* NightSkyGI =
			Cast<UNightSkyGameInstance>(GetGameInstance());

		if (!NightSkyGI)
		{
			return;
		}

		const bool bP2Complete =
			GameState && GameState->P2Charas.Num() >= CharNumP2;

		const bool bIsMultiplayer =
			NightSkyGI->FighterRunner == Multiplayer;

		if (bP2Complete || bIsMultiplayer)
		{
			if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
			{
				if (ANightSkyCharaPlayerSelectController* CharaSelectPC =
					Cast<ANightSkyCharaPlayerSelectController>(PC))
				{
					CharaSelectPC->PushMenu(StageSelectWidgetClass);
				}
			}
		}
	}
	else
	{
		if (bIsP1)
		{
			UNightSkyGameInstance* NightSkyGI =
				Cast<UNightSkyGameInstance>(GetGameInstance());

			if (!NightSkyGI)
			{
				return;
			}

			switch (NightSkyGI->FighterRunner)
			{
			case LocalPlay:
				{
					APlayerController* PC =
						UGameplayStatics::GetPlayerController(this, 0);

					if (ANightSkyMenuController* MenuPC =
						Cast<ANightSkyMenuController>(PC))
					{
						MenuPC->PushMenu(LocalPlayListWidgetClass);
					}

					break;
				}

			case Multiplayer:
				break;

			case SyncTest:
				break;

			default:
				break;
			}
		}
	}
}

void UNightSkyCharaSelectGrid::OnPromptConfirm_Implementation(int32 PromptIndex)
{
	switch (PromptIndex)
	{
	case 0:
		if (!MainMenuLevel.IsNull())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenuLevel);
		}
		break;

	default:
		break;
	}
}

