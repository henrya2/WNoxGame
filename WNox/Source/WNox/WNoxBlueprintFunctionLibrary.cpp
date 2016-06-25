#include "WNox.h"
#include "WNoxBlueprintFunctionLibrary.h"
#include "WNoxGameInstance.h"

UWNoxBlueprintFunctionLibrary::UWNoxBlueprintFunctionLibrary(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{

}

bool UWNoxBlueprintFunctionLibrary::FindItemInfo(UObject* WorldContextObject, const FString& ItemKey, FWNoxItemInfo& OutItemInfo)
{
	if (!WorldContextObject)
		return false;

	UWNoxGameInstance* WNoxGameInstance = Cast<UWNoxGameInstance>(WorldContextObject->GetWorld()->GetGameInstance());
	if (!WNoxGameInstance)
		return false;

	UItemInfoManager* ItemInfoManager = WNoxGameInstance->GetItemInfoManager();
	if (!ItemInfoManager)
		return false;

	return ItemInfoManager->FindItemInfo(ItemKey, OutItemInfo);
}

