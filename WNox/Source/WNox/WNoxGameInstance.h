#pragma once

#include "Engine/GameInstance.h"
#include "WNoxGameInstance.generated.h"

UCLASS(Blueprintable)
class UWNoxGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UWNoxGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	class UItemInfoManager* GetItemInfoManager() const { return ItemInfoManager; }

	virtual void Init() override;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, Category = "DataTable")
	class UItemInfoManager* ItemInfoManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable")
	class UDataTable* ItemInfoDataTable;
};
