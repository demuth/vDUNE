// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HighEnergyPhysicsEngine : ModuleRules
{
	public HighEnergyPhysicsEngine(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

	    PublicIncludePaths.AddRange(
            new string[]{
            "HighEnergyPhysicsEngine/Public"
        });

        PrivateIncludePaths.AddRange(
            new string[] {
            "HighEnergyPhysicsEngine/Private"
        });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

        PrivateDependencyModuleNames.AddRange(new string[] { "RenderCore", "Json", "JsonUtilities" });

        PrivateDependencyModuleNames.AddRange(new string[] { "vDuneCore" });
	}
}
