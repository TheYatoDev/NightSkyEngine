// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "NightSkyStageSelectButton.generated.h"

class UImage;
class UNightSkyStageSelectGrid;
class UPrimaryStageData;
/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyStageSelectButton : public UCommonButtonBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnClicked() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPrimaryStageData> StageData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNightSkyStageSelectGrid> Owner;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> ButtonImage;
	
	
};
