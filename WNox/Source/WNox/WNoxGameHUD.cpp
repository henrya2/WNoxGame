#include "WNox.h"
#include "WNoxGameHUD.h"
#include "WNoxGameMainUMG.h"

AWNoxGameHUD::AWNoxGameHUD()
{

}

void AWNoxGameHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GameMainUMGClass && GetOwningPlayerController())
	{
		GameMainUMG = CreateWidget<UWNoxGameMainUMG>(GetOwningPlayerController(), GameMainUMGClass);
		if (bShowHUD)
		{
			GameMainUMG->AddToPlayerScreen();
		}
	}
}
