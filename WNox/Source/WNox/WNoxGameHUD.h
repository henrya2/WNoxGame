#pragma once

#include "GameFramework/HUD.h"
#include "WNoxGameHUD.generated.h"

class UWNoxGameMainUMG;

UCLASS(Blueprintable)
class AWNoxGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AWNoxGameHUD();

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UMG|Class")
	TSubclassOf<UWNoxGameMainUMG> GameMainUMGClass;

	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "UMG")
	UWNoxGameMainUMG* GameMainUMG;
};
