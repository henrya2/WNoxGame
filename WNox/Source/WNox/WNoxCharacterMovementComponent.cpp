#include "WNox.h"
#include "WNoxCharacterMovementComponent.h"

UWNoxCharacterMovementComponent::UWNoxCharacterMovementComponent(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	bUseAccelerationForPaths = true;
}

