#pragma once

#include "SpawningVolumeCommons.h"
#include "SpawningVolumeInterface.generated.h"

UINTERFACE(NotBlueprintable, meta = (CannotImplementInterfaceInBlueprint))
class USpawningVolumeInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ISpawningVolumeInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	virtual void AddSpawnActorDisappearDelegate(const FOnSpawnedActorDisappearDelegate& InDelegate) = 0;
};