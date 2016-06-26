// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "WNoxGameState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class WNOX_API AWNoxGameState : public AGameState
{
	GENERATED_BODY()

	friend class AWNoxGameMode;

public:
	AWNoxGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Transient, Category = "Game")
	int32 DoorLife;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Game")
	int32 InitialDoorlife;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Transient, Category = "Game")
	int32 TotalKillCount;
};
