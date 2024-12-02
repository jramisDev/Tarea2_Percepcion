// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tarea2_Percepcion : ModuleRules
{
	public Tarea2_Percepcion(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		//PublicIncludePaths.Add(ModuleDirectory);
	}
}
