// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TestingGround_UE4GameMode.h"
#include "TestingGround_UE4HUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestingGround_UE4GameMode::ATestingGround_UE4GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestingGround_UE4HUD::StaticClass();
}
