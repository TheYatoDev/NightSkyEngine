// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyStageSelectGrid.h"
#include "CommonTextBlock.h"
#include "NightSkyCharaPlayerSelectController.h"
#include "NightSkyCharaSelectGameState.h"
#include "NightSkyStageSelectButton.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "NightSkyEngine/Battle/Objects/PlayerObject.h"
#include "NightSkyEngine/Data/PrimaryStageData.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "NightSkyEngine/Network/FighterRunners.h"

void UNightSkyStageSelectGrid::NativeConstruct()
{
	Super::NativeConstruct();

	ANightSkyCharaSelectGameState* CharaSelectGS =
		Cast<ANightSkyCharaSelectGameState>(GetWorld()->GetGameState());
	if (!CharaSelectGS) return;

	GameState = CharaSelectGS;

	if (!StageBox) return;

	CharaSelectGS->GatherStageData();
	StageBox->ClearChildren();

	for (UPrimaryStageData* StageData : CharaSelectGS->StageDatas)
	{
		UNightSkyStageSelectButton* StageButton =
			CreateWidget<UNightSkyStageSelectButton>(GetOwningPlayer(), StageSelectButtonClass);

		if (!StageButton) continue;

		StageButton->StageData = StageData;
		StageButton->Owner = this;

		StageBox->AddChild(StageButton);
	}
}

void UNightSkyStageSelectGrid::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	/*FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		if (UWidget* FocusTarget = GetDesiredFocusTarget())
		{
			FocusTarget->SetFocus();
			FocusTarget->SetUserFocus(GetOwningPlayer());
		}
	}, 0.2f, false);*/
	if (IntroAnimation)
	{
		PlayAnimation(IntroAnimation);
        
		FWidgetAnimationDynamicEvent AnimFinished;
		AnimFinished.BindDynamic(this, &UNightSkyStageSelectGrid::OnIntroAnimationFinished);
		BindToAnimationFinished(IntroAnimation, AnimFinished);
	}
}

UWidget* UNightSkyStageSelectGrid::NativeGetDesiredFocusTarget() const
{
	UE_LOG(LogTemp, Warning, TEXT("NativeGetDesiredFocusTarget - StageBox children=%d"),
	   StageBox ? StageBox->GetChildrenCount() : -1);
	if (StageBox)
	{
		return StageBox->GetChildAt(0);
	}
	return nullptr;
}

bool UNightSkyStageSelectGrid::NativeOnHandleBackAction()
{
	if (!GameState) return true;

    DeactivateWidget();

    if (GameState->P1Charas.Num() == 0)
    {
        return true;
    }

    UNightSkyGameInstance* GI = Cast<UNightSkyGameInstance>(GetGameInstance());

    if (GameState->P2Charas.Num() > 0)
    {
        // Destroy all P2 charas
        for (AActor* Chara : GameState->P2Charas)
        {
            if (Chara) Chara->Destroy();
        }
        GameState->P2Charas.Empty();

        if (!GI) return true;

        FBattleData& BattleData = GI->BattleData;
        int32 TempIndex = BattleData.PlayerListP2.Num() / 2;
        while (TempIndex > 0)
        {
            BattleData.PlayerListP2[TempIndex] = nullptr;
            BattleData.ColorIndicesP2[TempIndex] = 0;
            TempIndex--;
        }
    }
    else
    {
        // P2Charas empty — push prompt and destroy P1
        APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
        if (ANightSkyCharaPlayerSelectController* CharaSelectPC =
            Cast<ANightSkyCharaPlayerSelectController>(PC))
        {
            CharaSelectPC->PushPrompt(
                FText::FromString("Are you sure you wish to return to the main menu?"),
                this, 0);
        }

        for (AActor* Chara : GameState->P1Charas)
        {
            if (Chara) Chara->Destroy();
        }
        GameState->P1Charas.Empty();

        if (!GI) return true;

        FBattleData& BattleData = GI->BattleData;

        BattleData.PlayerListP1.Empty();
        BattleData.PlayerListP1.SetNum(6);
        BattleData.ColorIndicesP1.Empty();
        BattleData.ColorIndicesP1.SetNum(6);
        BattleData.PlayerListP2.Empty();
        BattleData.PlayerListP2.SetNum(6);
        BattleData.ColorIndicesP2.Empty();
        BattleData.ColorIndicesP2.SetNum(6);

        int32 TempIndex = BattleData.PlayerListP1.Num() / 2;
        while (TempIndex > 0)
        {
            BattleData.PlayerListP1[TempIndex] = nullptr;
            BattleData.ColorIndicesP1[1] = 0;
            TempIndex--;
        }
    }

    return true;
}

void UNightSkyStageSelectGrid::OnStageHovered(FText Name)
{
	if (SelectedStage)
	{
		SelectedStage->SetText(Name);
	}
}

void UNightSkyStageSelectGrid::OnStageSelected(UPrimaryStageData* Stage)
{
	UNightSkyGameInstance* NightSkyGI = Cast<UNightSkyGameInstance>(GetGameInstance());
	if (!NightSkyGI) return;

	NightSkyGI->BattleData.Stage = Stage;
	
	UE_LOG(LogTemp, Warning, TEXT("OnStageSelected - Stage=%s, BattleData.Stage=%s"),
	   Stage ? *Stage->GetName() : TEXT("null"),
	   NightSkyGI->BattleData.Stage ? *NightSkyGI->BattleData.Stage->GetName() : TEXT("null"));

	OnStageConfirm();
}

void UNightSkyStageSelectGrid::OnStageConfirm()
{
	UNightSkyGameInstance* NightSkyGI = Cast<UNightSkyGameInstance>(GetGameInstance());
	if (!NightSkyGI) return;

	switch (NightSkyGI->FighterRunner)
	{
	case LocalPlay:
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(this, VSInfoLevel);
			break;
		}
	case Multiplayer:
	case SyncTest:
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
			ANightSkyCharaPlayerSelectController* CharaSelectPC =
				Cast<ANightSkyCharaPlayerSelectController>(PC);
			if (!CharaSelectPC) return;

			if (NightSkyGI->IsHost)
			{
				CharaSelectPC->HostGame();
			}
			else
			{
				FBattleData& BattleData = NightSkyGI->BattleData;
				BattleData.PlayerListP2 = BattleData.PlayerListP1;

				CharaSelectPC->PushMenu(LobbyListWidgetClass);
			}
			break;
		}
	default:
		break;
	}
}

void UNightSkyStageSelectGrid::OnPromptConfirm_Implementation(int32 PromptIndex)
{
	Super::OnPromptConfirm_Implementation(PromptIndex);

	switch (PromptIndex)
	{
	case 0:
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenuLevel);
			break;
		}
	default:
		break;
	}
}

void UNightSkyStageSelectGrid::OnIntroAnimationFinished()
{
	if (UWidget* FocusTarget = GetDesiredFocusTarget())
	{
		FocusTarget->SetFocus();
		FocusTarget->SetUserFocus(GetOwningPlayer());
	}
}
