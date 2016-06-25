#pragma once

#include "Engine/DataTable.h"
#include "ItemInfo.generated.h"

UENUM(BlueprintType)
enum class EItemInfoMatchType : uint8
{
	Apple,
	Pear,
	Tail,
};

USTRUCT(BlueprintType)
struct FItemInfoTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MatchType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
};

USTRUCT(BlueprintType)
struct FWNoxItemInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString ItemKey;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FItemInfoTableRow TableRowInfo;
};

UCLASS(Blueprintable)
class UItemInfoManager : public UObject
{
	GENERATED_BODY()

public:
	UItemInfoManager();

	UFUNCTION(BlueprintCallable, Category = "DataTable")
	void LoadDataTable(const FString& AssetPath);

	UFUNCTION(BlueprintCallable, Category = "DataTable")
	void SetFromDataTableObject(class UDataTable* InDataTable);

	UFUNCTION(BlueprintCallable, Category = "DataTable")
	bool FindItemInfo(const FString& ItemKey, FWNoxItemInfo& OutItemInfo);

	const TArray<FWNoxItemInfo>& GetAllItemInfos() const { return AllItemInfos; }

	void SetCurrentWorld(class UWorld* InWorld );

	virtual class UWorld* GetWorld() const override;

protected:
	TWeakObjectPtr<class UWorld> CurrentWorld;

	UPROPERTY(VisibleAnywhere, Category = "DataTable")
	UDataTable* ItemInfoDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable")
	TArray<FWNoxItemInfo> AllItemInfos;
};
