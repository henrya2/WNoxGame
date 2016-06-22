#pragma once

#include "AIController.h"
#include "MonsterController.generated.h"

UCLASS()
class AMonsterController : public AAIController
{
	GENERATED_BODY()

public:
	AMonsterController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};