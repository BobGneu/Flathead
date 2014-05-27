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
            Path.Combine(ThirdPartyPath, "v8", "Includes"),
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

        LoadV8(Target);
    }

    private bool LoadV8(TargetInfo Target)
    {
        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            string PlatformString;
            string LibrariesPath = Path.Combine(ThirdPartyPath, "v8", "Libraries", "Windows");

            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PlatformString = "x64";
                LibrariesPath = Path.Combine(LibrariesPath, "x64");
            }
            else
            {
                PlatformString = "ia32";
                LibrariesPath = Path.Combine(LibrariesPath, "x86");
            }

            LibrariesPath = Path.Combine(LibrariesPath, "Release");

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "icui18n.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "icuuc.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_base." + PlatformString + ".lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_nosnapshot." + PlatformString + ".lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "v8_snapshot.lib"));

            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "v8", "Includes"));

            Definitions.Add(string.Format("WITH_FLATHEAD=1"));

            return true;
        }

        Definitions.Add(string.Format("WITH_FLATHEAD=0"));
        return false;
    }
}
