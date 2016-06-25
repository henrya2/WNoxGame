#include "WNox.h"
#include "MonsterCharacter.h"
#include "ItemActionsInterface.h"

AMonsterCharacter::AMonsterCharacter(const FObjectInitializer& ObjectInitailzer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitailzer)
{

}

void AMonsterCharacter::HandlePawnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!HasAuthority())
		return;

	if (OtherActor->GetClass()->ImplementsInterface(UItemActionsInterface::StaticClass()))
	{
		bool bResult = IItemActionsInterface::Execute_MatchItem(OtherActor, ItemInfo.TableRowInfo.MatchType);
		OnMatchItemResult(bResult);
	}
}

void AMonsterCharacter::NotifyDisappear()
{
	ActorDisappearDelegate.Broadcast(this);
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonsterCharacter::HandlePawnOverlap);
	}
}

void AMonsterCharacter::AddSpawnActorDisappearDelegate(const FOnSpawnedActorDisappearDelegate& InDelegate)
{
	ActorDisappearDelegate.Add(InDelegate);
}
