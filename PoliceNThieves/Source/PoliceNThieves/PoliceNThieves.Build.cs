using UnrealBuildTool;

public class PoliceNThieves : ModuleRules
{
    public PoliceNThieves(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
    }
}

//// Copyright Epic Games, Inc. All Rights Reserved.

//using UnrealBuildTool;

//public class PoliceNThieves : ModuleRules
//{
//	public PoliceNThieves(ReadOnlyTargetRules Target) : base(Target)
//	{
//		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

//		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
//	}
//}

// Copyright Epic Games, Inc. All Rights Reserved.