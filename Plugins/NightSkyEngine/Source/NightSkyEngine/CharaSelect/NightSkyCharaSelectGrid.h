// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "NightSkyCharaSelectGameState.h"
#include "NightSkyCSelectButton.h"
#include "NightSkyEngine/UI/ExtendedCommonActivatableWidget.h"
#include "NightSkyCharaSelectGrid.generated.h"

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

	//
	// Widget Bindings
	//

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCommonBorder> MainBorder;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UOverlay> MainOverlay;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWrapBox> CharBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCommonTextBlock> SelectedP1;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UCommonTextBlock> SelectedP2;

	//
	// Button Class
	//

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Select")
	TSubclassOf<UNightSkyCSelectButton> ButtonClass;

	//
	// Runtime Buttons
	//

	UPROPERTY()
	TArray<TObjectPtr<UNightSkyCSelectButton>> Buttons;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharNumP1 = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharNumP2 = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsP1 = true;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ANightSkyCharaSelectGameState> GameState;

protected:
	void PopulateButtons();

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	UFUNCTION(BlueprintCallable)
	void SetCharNum();
	
public:
	UFUNCTION(BlueprintCallable)
	void OnCharaHovered(FText Name);
	
	UFUNCTION(BlueprintCallable)
	void OnCharaSelected(UPrimaryCharaData* Player);
};
