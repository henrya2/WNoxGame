// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "WNox.h"
#include "WNoxGameMode.h"
#include "WNoxPlayerController.h"
#include "WNoxCharacter.h"
#include "WNoxGameHUD.h"
#include "WNoxGameState.h"

AWNoxGameMode::AWNoxGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AWNoxPlayerController::StaticClass();

	DefaultPawnClass = AWNoxCharacter::StaticClass();

	HUDClass = AWNoxGameHUD::StaticClass();

	GameStateClass = AWNoxGameState::StaticClass();
}

void AWNoxGameMode::ChangeDoorLife(int32 InLife)
{
	AWNoxGameState* WNoxGameState = Cast<AWNoxGameState>(GameState);
	if (WNoxGameState)
		WNoxGameState->DoorLife = InLife;

	if (CheckGameEnd())
	{
		ReturnToMainMenuHost();
	}
}

int32 AWNoxGameMode::GetDoorLife() const
{
	AWNoxGameState* WNoxGameState = Cast<AWNoxGameState>(GameState);
	if (WNoxGameState)
		return WNoxGameState->DoorLife;

	return 0;
}

bool AWNoxGameMode::CheckGameEnd() const
{
	AWNoxGameState* WNoxGameState = Cast<AWNoxGameState>(GameState);
	if (WNoxGameState)
		return WNoxGameState->DoorLife <= 0;

	return true;
}

void AWNoxGameMode::ChangeTotalKillCount(int32 InTotalKillCount)
{
	AWNoxGameState* WNoxGameState = Cast<AWNoxGameState>(GameState);
	if (WNoxGameState)
		WNoxGameState->TotalKillCount = InTotalKillCount;
}

int32 AWNoxGameMode::GetTotalKillCount() const
{
	AWNoxGameState* WNoxGameState = Cast<AWNoxGameState>(GameState);
	if (WNoxGameState)
		return WNoxGameState->TotalKillCount;

	return 0;
}
