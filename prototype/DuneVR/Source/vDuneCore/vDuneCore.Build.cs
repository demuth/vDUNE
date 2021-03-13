// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class vDuneCore : ModuleRules
{
	public vDuneCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

	    PublicIncludePaths.AddRange(
            new string[]{
            "vDuneCore/Public"
        });

        PrivateIncludePaths.AddRange(
            new string[] {
            "vDuneCore/Private"
        });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

        PrivateDependencyModuleNames.AddRange(new string[] { "RenderCore", "Json", "JsonUtilities" });
	}
}
