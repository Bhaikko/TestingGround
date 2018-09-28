// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestingGround_UE4HUD.generated.h"

UCLASS()
class ATestingGround_UE4HUD : public AHUD
{
	GENERATED_BODY()

public:
	ATestingGround_UE4HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

