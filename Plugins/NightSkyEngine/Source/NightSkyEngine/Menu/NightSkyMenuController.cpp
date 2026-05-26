// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyMenuController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "NightSkyEngine/CharaSelect/NightSkyCharaPlayerSelectController.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"
#include "NightSkyEngine/Network/NSESessionSubsystem.h"
#include "NightSkyEngine/Online/NightSkyLobbyItemWidget.h"
#include "NightSkyEngine/Online/NightSkyLobbyListWidget.h"
#include "NightSkyEngine/UI/NightSkyUIBaseWidget.h"

void ANightSkyMenuController::BeginPlay()
{
	Super::BeginPlay();

	// Bind session complete event
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UNSESessionSubsystem* NSESessionSubsystem = GI->GetSubsystem<UNSESessionSubsystem>())
		{
			NSESessionSubsystem->OnFindSessionsCompleteEvent.AddDynamic(
			this,
			&ANightSkyCharaPlayerSelectController::HandleFindSessionsComplete
		);
		}

		// Add input mapping context
		if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSubsystem->AddMappingContext(MenuMappingContext, 0);
			}
		}
	}
}

void ANightSkyMenuController::HandleFindSessionsComplete(const TArray<FNSESessionInfo>& Sessions, bool bSuccessful)
{
	{
		if (!bSuccessful)
		{
			return;
		}

		TArray<UUserWidget*> FoundWidgets;

		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, LobbyListWidgetClass, false);

		if (FoundWidgets.Num() <= 0)
		{
			return;
		}

		UNightSkyLobbyListWidget* LobbyListWidget = Cast<UNightSkyLobbyListWidget>(FoundWidgets[0]);

		if (!LobbyListWidget || !LobbyListWidget->LobbyList)
		{
			return;
		}

		LobbyListWidget->LobbyList->ClearChildren();

		for (const FNSESessionInfo& SessionInfo : Sessions)
		{
			UNightSkyLobbyItemWidget* LobbyItem = CreateWidget<UNightSkyLobbyItemWidget>(this, LobbyItemWidgetClass);

			if (!LobbyItem)
			{
				continue;
			}

			LobbyItem->SessionInfo = SessionInfo;

			LobbyListWidget->LobbyList->AddChild(LobbyItem);
		}
	}
}

void ANightSkyMenuController::PushMenu(TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (UIBaseWidget)
	{
		UIBaseWidget->PushMenu(WidgetClass);
	}
}

void ANightSkyMenuController::PushPrompt(FText PromptText, UExtendedCommonActivatableWidget* PromptOwner, int32 PromptIndex)
{
	if (!UIBaseWidget)
	{
		return;
	}
	
	UIBaseWidget->PushPrompt(PromptText, PromptOwner, PromptIndex);
}

void ANightSkyMenuController::PushModal(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
	if (!UIBaseWidget)
	{
		return;
	}

	UIBaseWidget->PushModal(ActivatableWidgetClass);
}

void ANightSkyMenuController::HostGame()
{
	UNightSkyGameInstance* NightSkyGI = Cast<UNightSkyGameInstance>(GetGameInstance());

	if (NightSkyGI)
	{
		NightSkyGI->FighterRunner = Multiplayer;
	}

	if (!ConnectingLevel.IsNull())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, ConnectingLevel, true, TEXT("listen"));
	}
}

void ANightSkyMenuController::JoinGame()
{
	UNightSkyGameInstance* NightSkyGI = Cast<UNightSkyGameInstance>(GetGameInstance());

	if (NightSkyGI)
	{
		NightSkyGI->FighterRunner = Multiplayer;
	}
	
	//Find LobbyList Widget
	TArray<UUserWidget*> FoundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, LobbyListWidgetClass, false);

	if (FoundWidgets.Num() > 0)
	{
		UNightSkyLobbyListWidget* LobbyListWidget = Cast<UNightSkyLobbyListWidget>(FoundWidgets[0]);

		if (LobbyListWidget && LobbyListWidget->LobbyList)
		{
			LobbyListWidget->LobbyList->ClearChildren();
		}
	}
	
	// Find Sessions
	if (UGameInstance* GI = GetGameInstance())
	{
		if (UNSESessionSubsystem* SessionSubsystem = GI->GetSubsystem<UNSESessionSubsystem>())
		{
			SessionSubsystem->FindSessions(100, false);
		}
	}
}

