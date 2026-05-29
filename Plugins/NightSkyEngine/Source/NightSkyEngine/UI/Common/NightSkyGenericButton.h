// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "NightSkyGenericButton.generated.h"

class UImage;
class UCommonTextBlock;
class UOverlay;
/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyGenericButton : public UCommonButtonBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UOverlay> MainOverlay;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> DisplayedText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> ButtonImage;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button")
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button")
	TObjectPtr<UTexture2D> Image;
};
