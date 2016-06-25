#include "WNox.h"
#include "ItemSpawningVolume.h"
#include "ItemActor.h"
#include "Engine/World.h"
#include "TimerManager.h"

AItemSpawningVolume::AItemSpawningVolume(const FObjectInitializer& ObjectIntializer /*=FObjectInitializer::Get()*/)
	: Super(ObjectIntializer)
{

}

void AItemSpawningVolume::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AItemSpawningVolume::OnPrepareSpawning_Implementation()
{
	CopyChildTypeArrayToBaseTypeArray(SpawningItemTypes, SpawningTypes);
}
