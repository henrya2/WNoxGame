#include "WNox.h"
#include "ItemInfo.h"

UItemInfoManager::UItemInfoManager()
{
	CurrentWorld = nullptr;
}

void UItemInfoManager::LoadDataTable(const FString& AssetPath)
{
	UDataTable* NewDataTable = LoadObject<UDataTable>(this, *AssetPath);
	SetFromDataTableObject(NewDataTable);
}

void UItemInfoManager::SetFromDataTableObject(class UDataTable* InDataTable)
{
	if (InDataTable && InDataTable->RowStruct && InDataTable->RowStruct->IsChildOf(FItemInfoTableRow::StaticStruct()))
	{
		for (auto Iter : InDataTable->RowMap)
		{
			FWNoxItemInfo ItemInfo{ Iter.Key.ToString(), *((FItemInfoTableRow*)Iter.Value) };
			AllItemInfos.Add(ItemInfo);
		}

		ItemInfoDataTable = InDataTable;
	}
}

bool UItemInfoManager::FindItemInfo(const FString& ItemKey, FWNoxItemInfo& OutItemInfo)
{
	if (ItemInfoDataTable)
	{
		FItemInfoTableRow* ItemInfoTableRow = ItemInfoDataTable->FindRow<FItemInfoTableRow>(*ItemKey, TEXT("ItemInfoTableFind"));
		if (ItemInfoTableRow)
		{
			OutItemInfo.ItemKey = ItemKey;
			OutItemInfo.TableRowInfo = *ItemInfoTableRow;

			return true;
		}
	}

	return false;
}

void UItemInfoManager::SetCurrentWorld(class UWorld* InWorld)
{
	CurrentWorld = InWorld;
}

class UWorld* UItemInfoManager::GetWorld() const
{
	return CurrentWorld.Get();
}
