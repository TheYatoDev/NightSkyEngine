// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "NightSkyCSelectButton.generated.h"

class UNightSkyCharaSelectGrid;
class UPrimaryCharaData;
/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyCSelectButton : public UCommonButtonBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnClicked() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UOverlay> Overlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UImage> ButtonImage;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Select")
	TObjectPtr<UPrimaryCharaData> CharaData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Select")
	TObjectPtr<UNightSkyCharaSelectGrid> Owner;
	
	void InitButton(UPrimaryCharaData* InCharaData, UNightSkyCharaSelectGrid* InOwningGrid);
	
};
