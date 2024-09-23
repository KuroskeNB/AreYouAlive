// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AreYouAlive : ModuleRules
{
	public AreYouAlive(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput","HTTP","Json"});
	}
}
