// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DreamBox : ModuleRules
{
	public DreamBox(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Sockets" });
		PrivateDependencyModuleNames.AddRange(new string[] { "CableComponent" });
	}
}
