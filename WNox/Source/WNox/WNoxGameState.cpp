// Fill out your copyright notice in the Description page of Project Settings.

#include "WNox.h"
#include "WNoxGameState.h"
#include "UnrealNetwork.h"

AWNoxGameState::AWNoxGameState(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	DoorLife = 0;

	InitialDoorlife = 5;
}

void AWNoxGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWNoxGameState, DoorLife);
	DOREPLIFETIME(AWNoxGameState, InitialDoorlife);
	DOREPLIFETIME(AWNoxGameState, TotalKillCount);
}

void AWNoxGameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HasAuthority())
		DoorLife = InitialDoorlife;
}
