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
            // Path.Combine(ThirdPartyPath, "v8", "Includes"),
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
        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            string LibrariesPath = Path.Combine(ThirdPartyPath, "Flathead", "Libraries", "Windows");

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                LibrariesPath = Path.Combine(LibrariesPath, "x64");
            }
            else
            {
                LibrariesPath = Path.Combine(LibrariesPath, "x86");
            }

            LibrariesPath = Path.Combine(LibrariesPath, "Release");

            // PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "Flathead.dll"));
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "Flathead", "Includes"));

            Definitions.Add(string.Format("WITH_FLATHEAD=1"));

            return true;
        }

        Definitions.Add(string.Format("WITH_FLATHEAD=0"));
        return false;
    }
}
