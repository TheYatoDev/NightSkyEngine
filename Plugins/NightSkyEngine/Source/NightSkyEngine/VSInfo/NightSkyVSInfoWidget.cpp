// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyVSInfoWidget.h"
#include "Components/Image.h"
#include "NightSkyEngine/Data/PrimaryCharaData.h"
#include "NightSkyEngine/Miscellaneous/NightSkyGameInstance.h"

UWidget* UNightSkyVSInfoWidget::NativeGetDesiredFocusTarget() const
{
	return Super::NativeGetDesiredFocusTarget();
}

void UNightSkyVSInfoWidget::NativeConstruct()
{
	UNightSkyGameInstance* NightSkyGI = Cast<UNightSkyGameInstance>(GetGameInstance());
	if (!NightSkyGI) return;

	FBattleData& BattleData = NightSkyGI->BattleData;

	// Load P1 character
	UPrimaryCharaData* P1Asset = BattleData.PlayerListP1[0].LoadSynchronous();
	UPrimaryCharaData* P1Data = Cast<UPrimaryCharaData>(P1Asset);
	if (P1Data && P1Splash)
	{
		FSlateBrush Brush;
		Brush.DrawAs = ESlateBrushDrawType::Image;
		Brush.Tiling = ESlateBrushTileType::NoTile;
		Brush.Mirroring = ESlateBrushMirrorType::NoMirror;
		Brush.SetResourceObject(P1Data->CharaSplashIcon);
		P1Splash->SetBrush(Brush);
	}

	// Load P2 character
	UObject* P2Asset = BattleData.PlayerListP2[0].LoadSynchronous();
	UPrimaryCharaData* P2Data = Cast<UPrimaryCharaData>(P2Asset);
	if (P2Data && P2Splash)
	{
		FSlateBrush Brush;
		Brush.DrawAs = ESlateBrushDrawType::Image;
		Brush.Tiling = ESlateBrushTileType::NoTile;
		Brush.Mirroring = ESlateBrushMirrorType::NoMirror;
		Brush.SetResourceObject(P2Data->CharaSplashIcon);
		P2Splash->SetBrush(Brush);
	}
}
	
	