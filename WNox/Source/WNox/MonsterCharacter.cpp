#include "WNox.h"
#include "MonsterCharacter.h"
#include "ItemActionsInterface.h"
#include "UnrealNetwork.h"
#include "WNoxGameMode.h"

AMonsterCharacter::AMonsterCharacter(const FObjectInitializer& ObjectInitailzer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitailzer)
{
	bDeath = false;
}

void AMonsterCharacter::HandlePawnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!HasAuthority())
		return;

	if (bDeath)
		return;

	if (OtherActor->GetClass()->ImplementsInterface(UItemActionsInterface::StaticClass()))
	{
		bool bResult = IItemActionsInterface::Execute_MatchItem(OtherActor, ItemInfo.TableRowInfo.MatchType);
		OnMatchItemResult(bResult);
		if (bResult)
		{
			SetActorEnableCollision(false);
			bDeath = true;

			AWNoxGameMode* GameMode = Cast<AWNoxGameMode>(UGameplayStatics::GetGameMode(this));
			if (GameMode)
			{
				GameMode->ChangeTotalKillCount(GameMode->GetTotalKillCount() + 1);
			}
		}
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

void AMonsterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMonsterCharacter, bDeath);
}
