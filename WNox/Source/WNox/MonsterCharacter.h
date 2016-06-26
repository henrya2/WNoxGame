#pragma once

#include "GameFramework/Character.h"
#include "SpawningVolumeInterface.h"
#include "ItemInfo.h"
#include "MonsterCharacter.generated.h"

UCLASS(Blueprintable)
class AMonsterCharacter 
	: public ACharacter
	, public ISpawningVolumeInterface
{
	GENERATED_BODY()

public:
	AMonsterCharacter(const FObjectInitializer& ObjectInitailzer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void HandlePawnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintImplementableEvent, Category = "Item")
	void OnMatchItemResult(bool bMatched);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void NotifyDisappear();

	virtual void BeginPlay() override;

	virtual void AddSpawnActorDisappearDelegate(const FOnSpawnedActorDisappearDelegate& InDelegate) override;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FWNoxItemInfo ItemInfo;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadWrite, Transient, Category = "Life")
	uint32 bDeath : 1;

	FOnSpawnedActorDisappearMultiDelegate ActorDisappearDelegate;
};