#pragma once

#include "SpawningVolumeBase.h"
#include "ItemSpawningVolume.generated.h"

UCLASS(Blueprintable)
class AItemSpawningVolume : public ASpawningVolumeBase
{
	GENERATED_BODY()

public:
	AItemSpawningVolume(const FObjectInitializer& ObjectIntializer = FObjectInitializer::Get());

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void OnPrepareSpawning_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TArray<TSubclassOf<class AItemActor>> SpawningItemTypes;
};
