#pragma once

#include "UMG.h"
#include "WNoxGameMainUMG.generated.h"

UCLASS(Blueprintable)
class UWNoxGameMainUMG : public UUserWidget
{
	GENERATED_BODY()

public:
	UWNoxGameMainUMG(const FObjectInitializer& ObjectInitalizer = FObjectInitializer::Get());
};