// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/UI/ExtendedCommonActivatableWidget.h"
#include "NightSkyWardrobeSelect.generated.h"

class UCommonTextBlock;
class UCommonNumericTextBlock;
class UHorizontalBox;
class UNightSkyGenericButton;
class UVerticalBox;
class UOverlay;
class UNightSkyCharaSelectGrid;
/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyWardrobeSelect : public UExtendedCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual bool NativeOnHandleBackAction() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UOverlay> MainOverlay;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> MainVerticalBox;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> SkinBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UNightSkyGenericButton> SkinLeftButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> SkinName;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UNightSkyGenericButton> SkinRightButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> ColorBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UNightSkyGenericButton> ColorLeftButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonNumericTextBlock> ColorIndex;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UNightSkyGenericButton> ColorRightButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UNightSkyGenericButton> Confirm;
	
	UFUNCTION()
	void HandleConfirmClicked();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNightSkyCharaSelectGrid> Owner;

	UPROPERTY(BlueprintReadOnly)
	bool bIsP1 = false;
	
};
