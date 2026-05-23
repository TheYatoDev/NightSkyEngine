// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NightSkyEngine/Network/NSESessionSubsystem.h"
#include "NightSkyMenuController.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API ANightSkyMenuController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<class UInputMappingContext> MenuMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Lobby")
	TSubclassOf<class UNightSkyLobbyListWidget> LobbyListWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Lobby")
	TSubclassOf<class UNightSkyLobbyItemWidget> LobbyItemWidgetClass;
	
	UFUNCTION()
    void HandleFindSessionsComplete(const TArray<FNSESessionInfo>& Sessions, bool bWasSuccessful);
	
};
