// Copyright 2013 Gneu, LLC. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class Flathead : ModuleRules
{
    /// <summary>
    /// Accessor for the Module's path
    /// </summary>
    protected string ModulePath
    {
        get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
    }

    /// <summary>
    /// Accessor for thee ThirdParty Path. 
    /// </summary>
    protected string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "..", "..", "ThirdParty")); }
    }

    public Flathead(TargetInfo Target)
    {
        PrivateIncludePaths.AddRange(new string[] 
        { 
            Path.Combine("Flathead", "Private") 
        });
        
        PublicIncludePaths.AddRange(new string[] 
        { 
            Path.Combine("Flathead", "Public") 
        });

        PublicDependencyModuleNames.AddRange(new string[] 
        { 
            "Engine", 
            "Core" 
        });

       LoadFlathead(Target);
    }

    private bool LoadFlathead(TargetInfo Target)
    {
        if ((Target.Platform != UnrealTargetPlatform.Win64) && (Target.Platform != UnrealTargetPlatform.Win32))
        {
            Definitions.Add(string.Format("WITH_FLATHEAD=0"));
            return false;
        }

        string LibrariesPath = Path.Combine(ThirdPartyPath, "FlatheadCore", "lib", (Target.Platform == UnrealTargetPlatform.Win64 ? "x64" : "x86"));

        PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Core.lib"));

        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath));

        Definitions.Add(string.Format("WITH_FLATHEAD=1"));

        return true;
    }
}
