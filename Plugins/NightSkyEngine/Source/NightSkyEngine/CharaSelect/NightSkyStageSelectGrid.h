// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/UI/ExtendedCommonActivatableWidget.h"
#include "NightSkyStageSelectGrid.generated.h"

class UPrimaryStageData;
class UNightSkyStageSelectButton;
class ANightSkyCharaSelectGameState;
class UWrapBox;
class UCommonTextBlock;
/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyStageSelectGrid : public UExtendedCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnActivated() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	virtual bool NativeOnHandleBackAction() override;
	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UWrapBox> StageBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UNightSkyStageSelectButton> StageSelectButtonClass;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> SelectedStage;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ANightSkyCharaSelectGameState> GameState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> VSInfoLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCommonActivatableWidget> LobbyListWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> MainMenuLevel;
	
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> IntroAnimation;
	
	UFUNCTION()
	void OnStageHovered(FText Name);
	
	UFUNCTION()
	void OnStageSelected(UPrimaryStageData* Stage);
	
	UFUNCTION(BlueprintCallable)
	void OnStageConfirm();
	
	virtual void OnPromptConfirm_Implementation(int32 PromptIndex) override;
	
	UFUNCTION()
	void OnIntroAnimationFinished();
};
