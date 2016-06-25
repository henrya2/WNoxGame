#pragma once

#include "ItemActionsInterface.generated.h"

UINTERFACE(Blueprintable)
class WNOX_API UItemActionsInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class WNOX_API IItemActionsInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Pickup", meta = (DisplayName = "Pickup Item"))
	bool PickupItem(class AItemActor* InItemActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Match", meta = (DisplayName = "Match Item"))
	bool MatchItem(int32 MatchType);
};
