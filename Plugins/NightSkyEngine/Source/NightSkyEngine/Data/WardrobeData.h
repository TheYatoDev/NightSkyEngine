// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkinData.h"
#include "Engine/DataAsset.h"
#include "WardrobeData.generated.h"

/**
 * 
 */
UCLASS()
class NIGHTSKYENGINE_API UWardrobeData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Wardrobe")
	TArray<USkinData*> Skins;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Wardrobe")
	//int32 DefaultSkinIndex = 1;

};
