#pragma once

#include "GameFramework/Actor.h"
#include "SpawningVolumeBase.generated.h"

UCLASS(Blueprintable)
class ASpawningVolumeBase : public AActor
{
	GENERATED_BODY()

public:
	ASpawningVolumeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	const TArray<class AActor*>& GetSpawnedItems() const { return SpawnedActor; }

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	virtual void StartSpawningProcess();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	virtual void StopSpawningProcess();

	UFUNCTION(BlueprintNativeEvent, Category = "Spawn")
	void ProcessIntervalSpawning();

	virtual void ProcessIntervalSpawning_Implementation();

	virtual void BeginPlay() override;


	virtual void BeginDestroy() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	template<typename LeftType, typename RightType>
	void CopyChildTypeArrayToBaseTypeArray(const TArray<TSubclassOf<LeftType>>& LeftArray, TArray<TSubclassOf<RightType>>& RightArray)
	{
		RightArray.Empty();

		for (int32 i = 0; i < LeftArray.Num(); ++i)
		{
			RightArray.Add(LeftArray[i]);
		}
	}

protected:
	virtual void HandleActorDisappear(class AActor* InActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Spawn")
	void OnPrepareSpawning();

	virtual void OnPrepareSpawning_Implementation();

protected:
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Spawn")
	TArray<TSubclassOf<class AActor>> SpawningTypes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Volume")
	class UBoxComponent* BoxVolume;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Spawn")
	TArray<class AActor*> SpawnedActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	int32 MaxSpawningItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	float SpawningIntervalSeconds;

	UPROPERTY(VisibleInstanceOnly, Category = "Spawn")
	FTimerHandle SpawningTimerHandle;
};