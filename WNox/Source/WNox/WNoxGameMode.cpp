// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "WNox.h"
#include "WNoxGameMode.h"
#include "WNoxPlayerController.h"
#include "WNoxCharacter.h"
#include "WNoxGameHUD.h"

AWNoxGameMode::AWNoxGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AWNoxPlayerController::StaticClass();

	DefaultPawnClass = AWNoxCharacter::StaticClass();

	HUDClass = AWNoxGameHUD::StaticClass();
}