// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/UI/ExtendedCommonActivatableWidget.h"
#include "NightSkyLobbyListWidget.generated.h"

class UOverlay;
class UVerticalBox;
class UCommonBorder;
class UHorizontalBox;
class UCommonButtonBase;
class UScrollBox;

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyLobbyListWidget : public UExtendedCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> MainOverlay;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> RootVerticalBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonBorder> MainBorder;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> LobbyList;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> ButtonRow;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> RefreshButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> CloseButton;
	
};
