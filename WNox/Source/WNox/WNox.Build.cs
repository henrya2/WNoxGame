// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WNox : ModuleRules
{
	public WNox(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "AIModule",
            "Slate",
            "SlateCore",
            "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "OnlineSubsystem",
            "OnlineSubsystemUtils"
        });
    }
}
