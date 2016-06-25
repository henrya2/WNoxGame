#include "WNox.h"
#include "ItemActor.h"
#include "ItemActionsInterface.h"
#include "WNoxBlueprintFunctionLibrary.h"

AItemActor::AItemActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	RootComponent = Mesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	MaxLifeTime = 4.0f;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bReplicates = true;
}

void AItemActor::NotifyItemDisappear()
{
	ItemDisappearMultiDelgate.Broadcast(this);
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		FTimerHandle EmptyTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(EmptyTimerHandle, this, &AItemActor::ProcessLifeTimeEnd, FMath::RandRange(MinLifeTime, MaxLifeTime), false);

		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::HandleCollisionBoxOverlap);
	}

	if (!ItemInfo.ItemKey.IsEmpty())
	{
		bool bFoundItemInfo = UWNoxBlueprintFunctionLibrary::FindItemInfo(this, ItemInfo.ItemKey, ItemInfo);
	}
}

void AItemActor::ProcessLifeTimeEnd()
{
	NotifyItemDisappear();

	Destroy();
}

void AItemActor::OnPickup_Implementation()
{
	if (HasAuthority())
	{
		NotifyItemDisappear();

		Destroy();
	}
}

void AItemActor::HandleCollisionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!HasAuthority())
		return;

	bool bBePicked = false;

	if (OtherActor->GetClass()->ImplementsInterface(UItemActionsInterface::StaticClass()))
	{
		bBePicked = IItemActionsInterface::Execute_PickupItem(OtherActor, this);
	}

	if (bBePicked)
	{
		OnPickup();
	}
}

void AItemActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AItemActor::AddSpawnActorDisappearDelegate(const FOnSpawnedActorDisappearDelegate& InDelegate)
{
	ItemDisappearMultiDelgate.Add(InDelegate);
}
