// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NightSkyEngine/UI/ExtendedCommonActivatableWidget.h"
#include "NightSkyVSInfoWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UNightSkyVSInfoWidget : public UExtendedCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> P1Splash;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> P2Splash;
};
