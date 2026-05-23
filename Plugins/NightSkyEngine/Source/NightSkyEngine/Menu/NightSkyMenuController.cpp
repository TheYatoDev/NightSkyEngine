// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyMenuController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/ScrollBox.h"
#include "NightSkyEngine/CharaSelect/NightSkyCharaPlayerSelectController.h"

#include "NightSkyEngine/Network/NSESessionSubsystem.h"
#include "NightSkyEngine/Online/NightSkyLobbyItemWidget.h"
#include "NightSkyEngine/Online/NightSkyLobbyListWidget.h"

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

void ANightSkyMenuController::HandleFindSessionsComplete(const TArray<FNSESessionInfo>& Sessions, bool bWasSuccessful)
{
	{
		if (!bWasSuccessful)
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

