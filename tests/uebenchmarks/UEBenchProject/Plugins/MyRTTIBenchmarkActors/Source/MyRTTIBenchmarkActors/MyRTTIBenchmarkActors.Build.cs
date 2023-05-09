// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class MyRTTIBenchmarkActors : ModuleRules
{
	public MyRTTIBenchmarkActors(ReadOnlyTargetRules Target) : base(Target)
	{
		CppStandard = CppStandardVersion.Cpp17;
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // NOTE: <myrtti>/tests/uebenchmarks/UEBenchProject/Plugins/MyRTTIBenchmarkActors/Source
		// Note it assumes we're in <myrtti>/tests/uebenchmarks/UEBenchProject/Plugins/MyRTTIBenchmarkActors
		var myRTTIRoot = Path.Combine(new[] { ModuleDirectory, "..", "..", "..", "..", "..", "..", ".."});

		PublicIncludePaths.Add(Path.Combine(new []
		{
			myRTTIRoot, "src", "myrtti", "include"
		}));

		PublicAdditionalLibraries.Add(Path.Combine(new string[] {
			Path.Combine(myRTTIRoot, "build", "lib", "libmyrtti.a")
		}));

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...
			}
			);
	}
}
