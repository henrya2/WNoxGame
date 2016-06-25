#include "WNox.h"
#include "MonsterSpawningVolume.h"
#include "MonsterCharacter.h"

AMonsterSpawningVolume::AMonsterSpawningVolume(const FObjectInitializer& ObjectIntializer /*=FObjectInitializer::Get()*/)
	: Super(ObjectIntializer)
{

}

void AMonsterSpawningVolume::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterSpawningVolume::OnPrepareSpawning_Implementation()
{
	CopyChildTypeArrayToBaseTypeArray(SpawningItemTypes, SpawningTypes);
}
