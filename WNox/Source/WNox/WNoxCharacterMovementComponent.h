#pragma once

#include "GameFramework/Character.h"
#include "WNoxCharacterMovementComponent.generated.h"

UCLASS(Blueprintable)
class UWNoxCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UWNoxCharacterMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};