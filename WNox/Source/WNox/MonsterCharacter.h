#pragma once

#include "GameFramework/Character.h"
#include "MonsterCharacter.generated.h"

UCLASS()
class AMonsterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMonsterCharacter(const FObjectInitializer& ObjectInitailzer = FObjectInitializer::Get());
};