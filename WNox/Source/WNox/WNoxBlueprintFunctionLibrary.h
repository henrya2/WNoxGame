#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemInfo.h"
#include "WNoxBlueprintFunctionLibrary.generated.h"

UCLASS()
class UWNoxBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UWNoxBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Item", meta = (WorldContext = "WorldContextObject"))
	static bool FindItemInfo(UObject* WorldContextObject, const FString& ItemKey, FWNoxItemInfo& OutItemInfo);
};