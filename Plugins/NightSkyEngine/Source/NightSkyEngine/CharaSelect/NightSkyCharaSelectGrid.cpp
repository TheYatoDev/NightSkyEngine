// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyCharaSelectGrid.h"
#include "Components/CanvasPanel.h"
#include "Components/WrapBox.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "NightSkyCSelectButton.h"
#include "NightSkyCharaPlayerSelectController.h"
#include "Kismet/GameplayStatics.h"
#include "NightSkyEngine/Battle/Objects/PlayerObject.h"
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

		//UE_LOG(LogTemp, Warning, TEXT("Spawned Button Class: %s"), *GetNameSafe(CSelectButton->GetClass()));
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

	CharaNumP1 = NightSkyGI->TeamSizeP1;
	CharaNumP2 = NightSkyGI->TeamSizeP2;
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
	UE_LOG(LogTemp, Warning, TEXT("OnCharaSelected ENTRY - Player=%s, bIsP1=%d"),
		Player ? *Player->GetName() : TEXT("null"), bIsP1);
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
		FSoftObjectPath PlayerPath(Player);

		const int32 ExistingIndex =
			NightSkyGI->BattleData.PlayerListP1.IndexOfByPredicate(
				[&PlayerPath](const TSoftObjectPtr<UPrimaryCharaData>& Entry)
				{
					return Entry.ToSoftObjectPath() == PlayerPath;
				}
			);

		if (CharaNumP1 > ExistingIndex || ExistingIndex == INDEX_NONE)
		{
			Index = CharaNumP1;
		}
	}
	else
	{
		if (NightSkyGI->BattleData.PlayerListP1.IsValidIndex(CharaNumP2 - 1))
		{
			Index = CharaNumP2;
		}
	}

	if (Index == INDEX_NONE)
	{
		return;
	}

	ANightSkyCharaSelectGameState* CharaSelectGS =
		GetWorld() ? GetWorld()->GetGameState<ANightSkyCharaSelectGameState>() : nullptr;

	if (!CharaSelectGS)
	{
		return;
	}

	CharaSelectGS->AddPlayerObject(Player, bIsP1);

	ANightSkyCharaPlayerSelectController* CharaSelectPC =
		Cast<ANightSkyCharaPlayerSelectController>(GetOwningPlayer());

	if (!CharaSelectPC)
	{
		return;
	}

	CharaSelectPC->PushModal(WardrobeSelectWidgetClass);

	/*if (bIsP1)
	{
		OnCharaConfirm();
	}*/
}

void UNightSkyCharaSelectGrid::OnCharaConfirm()
{
	const bool bP1Complete = GameState && GameState->P1Charas.Num() >= CharaNumP1;

	if (bP1Complete || !bIsP1)
	{
		bIsP1 = false;

		UNightSkyGameInstance* NightSkyGI =
			Cast<UNightSkyGameInstance>(GetGameInstance());

		if (!NightSkyGI) return;

		const bool bP2Complete =
			GameState && GameState->P2Charas.Num() >= CharaNumP2;

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

			if (!NightSkyGI) return;

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

bool UNightSkyCharaSelectGrid::NativeOnHandleBackAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Grid NativeOnHandleBackAction"));
	Back();
	return true;
}

void UNightSkyCharaSelectGrid::Back()
{
	if (!GameState) return;

    const bool bBranch = (GameState->P1Charas.Num() == 0) || bIsP1;

    if (bBranch)
    {
        bIsP1 = true;

        if (GameState->P1Charas.Num() > 0)
        {
            AActor* LastP1Chara = GameState->P1Charas.Last();
            if (LastP1Chara) LastP1Chara->Destroy();
            GameState->P1Charas.RemoveAt(GameState->P1Charas.Num() - 1);

            UNightSkyGameInstance* GI = Cast<UNightSkyGameInstance>(GetGameInstance());
            if (!GI) return;

            FBattleData& BattleData = GI->BattleData;
            int32 TempIndex = BattleData.PlayerListP1.Num() - 1;
            while (TempIndex > 0 && !BattleData.PlayerListP1[TempIndex].IsValid())
            {
                BattleData.PlayerListP1[TempIndex] = nullptr;
                BattleData.ColorIndicesP1[TempIndex] = 0;
                TempIndex--;
            }
        }
        else
        {
            APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
            if (ANightSkyCharaPlayerSelectController* CharaSelectPC =
                Cast<ANightSkyCharaPlayerSelectController>(PC))
            {
                CharaSelectPC->PushPrompt(
                    FText::FromString("Are you sure you wish to return to the main menu?"),
                    this, 0);
            }
        }
    }
    else
    {
        if (GameState->P2Charas.Num() == 0)
        {
            bIsP1 = true;
        	
        	if (SelectedP2)
        	{
        		SelectedP2->SetText(FText::GetEmpty());
        	}

            if (GameState->P1Charas.Num() > 0)
            {
                AActor* LastP1Chara = GameState->P1Charas.Last();
                if (LastP1Chara) LastP1Chara->Destroy();
                GameState->P1Charas.RemoveAt(GameState->P1Charas.Num() - 1);

                UNightSkyGameInstance* GI = Cast<UNightSkyGameInstance>(GetGameInstance());
                if (!GI) return;

                FBattleData& BattleData = GI->BattleData;
                int32 TempIndex = BattleData.PlayerListP1.Num() - 1;
                while (TempIndex > 0 && !BattleData.PlayerListP1[TempIndex].IsValid())
                {
                    BattleData.PlayerListP1[TempIndex] = nullptr;
                    BattleData.ColorIndicesP1[TempIndex] = 0;
                    TempIndex--;
                }
            }
        }
        else
        {
            AActor* LastP2Chara = GameState->P2Charas.Last();
            if (LastP2Chara) LastP2Chara->Destroy();
            GameState->P2Charas.RemoveAt(GameState->P2Charas.Num() - 1);

            UNightSkyGameInstance* GI = Cast<UNightSkyGameInstance>(GetGameInstance());
            if (!GI) return;

            FBattleData& BattleData = GI->BattleData;
            int32 TempIndex = BattleData.PlayerListP2.Num() - 1;
            while (TempIndex > 0 && !BattleData.PlayerListP2[TempIndex].IsValid())
            {
                BattleData.PlayerListP2[TempIndex] = nullptr;
                BattleData.ColorIndicesP2[TempIndex] = 0;
                TempIndex--;
            }
        }
    }
}

