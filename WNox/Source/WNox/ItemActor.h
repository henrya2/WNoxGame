#pragma once

#include "GameFramework/Actor.h"
#include "ItemInfo.h"
#include "SpawningVolumeInterface.h"
#include "ItemActor.generated.h"

UCLASS(Blueprintable)
class AItemActor 
	: public AActor
	, public ISpawningVolumeInterface
{
	GENERATED_BODY()

public:
	AItemActor(const FObjectInitializer& ObjectInitializer);

	const FWNoxItemInfo& GetItemInfo() const { return ItemInfo; }

	UFUNCTION(BlueprintCallable, Category = "Event")
	void NotifyItemDisappear();

	virtual void BeginPlay() override;

	void ProcessLifeTimeEnd();

	UFUNCTION(BlueprintNativeEvent, Category = "Pickup")
	void OnPickup();

	virtual void OnPickup_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	virtual void HandleCollisionBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void AddSpawnActorDisappearDelegate(const FOnSpawnedActorDisappearDelegate& InDelegate) override;

protected:
	FOnSpawnedActorDisappearMultiDelegate ItemDisappearMultiDelgate;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FWNoxItemInfo ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float MinLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float MaxLifeTime;
};
