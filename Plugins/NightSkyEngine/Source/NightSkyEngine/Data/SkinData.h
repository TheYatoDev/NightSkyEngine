// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MaterialData.h"
#include "Engine/DataAsset.h"
#include "SkinData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSkinMeshPart
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bCustomizableMesh = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(EditCondition="bCustomizableMesh", EditConditionHides))
	USkeletalMesh* Mesh = nullptr;
};

USTRUCT(BlueprintType)
struct FSkinColorVariant
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText ColorName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UMaterialData* MaterialData = nullptr;
};


UCLASS()
class NIGHTSKYENGINE_API USkinData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText SkinName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FSkinMeshPart> MeshParts;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FSkinColorVariant> ColorVariants;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//int32 DefaultColorIndex = 1;
	
};
