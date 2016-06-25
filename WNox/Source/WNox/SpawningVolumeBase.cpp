#include "WNox.h"
#include "SpawningVolumeBase.h"
#include "SpawningVolumeInterface.h"

ASpawningVolumeBase::ASpawningVolumeBase(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	BoxVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxVolume"));
	RootComponent = BoxVolume;

	MaxSpawningItems = 5;

	SpawningIntervalSeconds = 3.0f;

	bReplicates = true;
}

void ASpawningVolumeBase::StartSpawningProcess()
{
	GetWorld()->GetTimerManager().SetTimer(SpawningTimerHandle, this, &ASpawningVolumeBase::ProcessIntervalSpawning_Implementation, SpawningIntervalSeconds, true);
}

void ASpawningVolumeBase::StopSpawningProcess()
{
	if (GetWorld()->IsValidLowLevel())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawningTimerHandle);
	}
}

void ASpawningVolumeBase::ProcessIntervalSpawning_Implementation()
{
	if (SpawnedActor.Num() >= MaxSpawningItems || SpawningTypes.Num() <= 0)
		return;

	FVector VolumeExtent = BoxVolume->GetScaledBoxExtent();
	FVector Origin = BoxVolume->GetComponentLocation();

	float RandomX = FMath::RandRange(-VolumeExtent.X, VolumeExtent.X);
	float RandomY = FMath::RandRange(-VolumeExtent.Y, VolumeExtent.Y);

	FVector OffsetVector(RandomX, RandomY, 0);

	int32 ChoosedTypeIndex = FMath::RandRange(0, SpawningTypes.Num() - 1);
	TSubclassOf<class AActor> ChoosedItemType = SpawningTypes[ChoosedTypeIndex];

	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* NewItemActor = GetWorld()->SpawnActor<AActor>(ChoosedItemType, Origin + OffsetVector, FRotator::ZeroRotator, ActorSpawnParameters);
	if (NewItemActor)
	{
		//NewItemActor->OnDisappearDelegates.AddDynamic(this, &AItemSpawningVolume::HandleItemActorDisappear);
		ISpawningVolumeInterface* SpawningVolumeInterface = Cast<ISpawningVolumeInterface>(NewItemActor);
		if (SpawningVolumeInterface)
		{
			SpawningVolumeInterface->AddSpawnActorDisappearDelegate(FOnSpawnedActorDisappearDelegate::CreateUObject(this, &ASpawningVolumeBase::HandleActorDisappear));
		}

		SpawnedActor.Add(NewItemActor);
	}
}

void ASpawningVolumeBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		OnPrepareSpawning();
		StartSpawningProcess();
	}
}

void ASpawningVolumeBase::BeginDestroy()
{
	Super::BeginDestroy();

	if (HasAuthority())
	{
		if (SpawningTimerHandle.IsValid())
		{
			StopSpawningProcess();
		}
	}
}

void ASpawningVolumeBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ASpawningVolumeBase::HandleActorDisappear(class AActor* InActor)
{
	SpawnedActor.Remove(InActor);
}

void ASpawningVolumeBase::OnPrepareSpawning_Implementation()
{

}
