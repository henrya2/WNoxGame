// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "WNoxGameMode.generated.h"

UCLASS(MinimalAPI)
class AWNoxGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AWNoxGameMode();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void ChangeDoorLife(int32 InLife);

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetDoorLife() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool CheckGameEnd() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void ChangeTotalKillCount(int32 InTotalKillCount);

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetTotalKillCount() const;
};



