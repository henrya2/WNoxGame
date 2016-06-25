#include "WNox.h"
#include "WNoxGameInstance.h"
#include "ItemInfo.h"

UWNoxGameInstance::UWNoxGameInstance(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{

}

void UWNoxGameInstance::Init()
{
	Super::Init();

	ItemInfoManager = NewObject<UItemInfoManager>(this, TEXT("ItemInfoManager"));
	ItemInfoManager->SetCurrentWorld(GetWorld());
	ItemInfoManager->SetFromDataTableObject(ItemInfoDataTable);
}

