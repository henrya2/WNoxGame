#pragma once

#include "SpawningVolumeBase.h"
#include "MonsterSpawningVolume.generated.h"

UCLASS(Blueprintable)
class AMonsterSpawningVolume : public ASpawningVolumeBase
{
	GENERATED_BODY()

public:
	AMonsterSpawningVolume(const FObjectInitializer& ObjectIntializer = FObjectInitializer::Get());

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void OnPrepareSpawning_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TArray<TSubclassOf<class AMonsterCharacter>> SpawningItemTypes;
};
