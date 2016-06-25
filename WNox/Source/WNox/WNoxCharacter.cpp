// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "WNox.h"
#include "WNoxCharacter.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "WNoxCharacterMovementComponent.h"
#include "ItemActor.h"
#include "UnrealNetwork.h"

AWNoxCharacter::AWNoxCharacter(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/) 
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWNoxCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AWNoxCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AWNoxCharacter::PickupItem_Implementation(AItemActor *InItemActor)
{
	if (HasAuthority())
	{
		PickedItems.Add(InItemActor->GetItemInfo());
		if (GetNetMode() == NM_ListenServer)
		{
			OnRep_PickedItems();
		}
	}
	return true;
}

bool AWNoxCharacter::MatchItem_Implementation(int32 MatchType)
{
	if (!HasAuthority())
		return false;

	for (int32 i = 0; i < PickedItems.Num(); ++i)
	{
		if (PickedItems[i].TableRowInfo.MatchType == MatchType)
		{
			PickedItems.RemoveAtSwap(i);
			return true;
		}
	}

	return false;
}

void AWNoxCharacter::PostNetInit()
{
	Super::PostNetInit();
}

void AWNoxCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWNoxCharacter, PickedItems);
}

void AWNoxCharacter::OnRep_PickedItems()
{
	OnPickedItemsChanged.Broadcast(PickedItems);
}
