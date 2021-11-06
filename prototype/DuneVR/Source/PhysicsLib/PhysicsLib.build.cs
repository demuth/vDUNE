using System;
using System.IO;
using UnrealBuildTool;

public class PhysicsLib : ModuleRules
{
    public PhysicsLib(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        PublicDefinitions.Add("WITH_PHYSICSLIB=1");

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../../Libraries/PhysicsLib/include"));

        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../../Libraries/PhysicsLib/bin/", "libphysics.a"));
    }
}