// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/Network/NSESessionSubsystem.h"
#include "NightSkyEngine/UI/ExtendedCommonActivatableWidget.h"
#include "NightSkyLobbyItemWidget.generated.h"

class UOverlay;
class UVerticalBox;
class UCommonTextBlock;
class UCommonButtonBase;

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyLobbyItemWidget : public UExtendedCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> MainOverlay;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> RootVerticalBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> LobbyID;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> JoinButton;
	
	UPROPERTY(BlueprintReadWrite)
	FNSESessionInfo SessionInfo;
	
};
