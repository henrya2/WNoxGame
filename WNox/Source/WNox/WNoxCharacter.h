// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "ItemInfo.h"
#include "GameFramework/Character.h"
#include "ItemActionsInterface.h"
#include "WNoxCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterPickedItemsChangedDelegate, const TArray<FWNoxItemInfo>&, PickedItems);

UCLASS(Blueprintable)
class AWNoxCharacter 
	: public ACharacter
	, public IItemActionsInterface
{
	GENERATED_BODY()

public:
	AWNoxCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual bool PickupItem_Implementation(class AItemActor *InItemActor) override;

	virtual bool MatchItem_Implementation(int32 MatchType) override;

	virtual void PostNetInit() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_PickedItems();

	UPROPERTY(VisibleAnywhere, BlueprintAssignable, Category = "Items")
	FOnCharacterPickedItemsChangedDelegate OnPickedItemsChanged;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_PickedItems, Category = "Items")
	TArray<FWNoxItemInfo> PickedItems;
};

