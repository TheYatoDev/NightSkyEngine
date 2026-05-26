// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NightSkyEngine/Network/NSESessionSubsystem.h"
#include "NightSkyMenuController.generated.h"

class UExtendedCommonActivatableWidget;
class UCommonActivatableWidget;
/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API ANightSkyMenuController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default")
	TObjectPtr<class UInputMappingContext> MenuMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default")
	TSubclassOf<class UNightSkyLobbyListWidget> LobbyListWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default")
	TSubclassOf<class UNightSkyLobbyItemWidget> LobbyItemWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default")
	TSoftObjectPtr<UWorld> ConnectingLevel;
	
	UFUNCTION()
    void HandleFindSessionsComplete(const TArray<FNSESessionInfo>& Sessions, bool bSuccessful);
	
public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UNightSkyUIBaseWidget> UIBaseWidget;
	
	UFUNCTION(BlueprintCallable)
	void PushMenu(TSubclassOf<UCommonActivatableWidget> WidgetClass);
	
	UFUNCTION(BlueprintCallable)
	void PushPrompt(FText PromptText, UExtendedCommonActivatableWidget* PromptOwner, int32 PromptIndex);
	
	UFUNCTION(BlueprintCallable)
	void PushModal(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);
	
	UFUNCTION(BlueprintCallable)
	void HostGame();
	
	UFUNCTION(BlueprintCallable)
	void JoinGame();
	
};
