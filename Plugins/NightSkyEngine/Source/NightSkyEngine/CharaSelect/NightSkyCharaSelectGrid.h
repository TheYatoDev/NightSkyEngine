// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "NightSkyCharaSelectGameState.h"
#include "NightSkyCSelectButton.h"
#include "NightSkyEngine/UI/ExtendedCommonActivatableWidget.h"
#include "NightSkyCharaSelectGrid.generated.h"

class UNightSkyStageSelectButton;
class UNightSkyWardrobeSelect;
/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyCharaSelectGrid : public UExtendedCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnActivated() override;
	
	virtual bool NativeOnHandleBackAction() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCommonBorder> MainBorder;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> MainOverlay;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWrapBox> CharBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCommonTextBlock> SelectedP1;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> SelectedP2;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default")
	TSubclassOf<UNightSkyCSelectButton> ButtonClass;

	UPROPERTY()
	TArray<TObjectPtr<UNightSkyCSelectButton>> Buttons;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharaNumP1 = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharaNumP2 = 1;
	
	void PopulateButtons();

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	UFUNCTION(BlueprintCallable)
	void SetCharNum();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ANightSkyCharaSelectGameState> GameState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsP1 = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default")
	TSoftObjectPtr<UWorld> MainMenuLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default")
	TSubclassOf<UCommonActivatableWidget> LocalPlayListWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default")
	TSubclassOf<UCommonActivatableWidget> StageSelectWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Default")
	TSubclassOf<UCommonActivatableWidget> WardrobeSelectWidgetClass;
	
	UFUNCTION(BlueprintCallable)
	void OnCharaHovered(FText Name);
	
	UFUNCTION(BlueprintCallable)
	void OnCharaSelected(UPrimaryCharaData* Player);
	
	UFUNCTION(BlueprintCallable)
	void OnCharaConfirm();
	
	virtual void OnPromptConfirm_Implementation(int32 PromptIndex) override;
	
	UFUNCTION(BlueprintCallable)
	void Back();
	
};
