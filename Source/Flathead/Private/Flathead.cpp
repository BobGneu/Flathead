#include "../Public/Flathead.h"
#include "FlatheadPCH.h"

DEFINE_LOG_CATEGORY(LogFlathead);

using namespace FH;

void FlatheadModule::StartupModule()
{
	FlatheadDLLHandle = null;

	if (!LoadFHDLL())
	{

	}
}

void FlatheadModule::ShutdownModule()
{
	ReleaseFHDLL();
}

int FlatheadModule::LoadFHDLL()
{
#if PLATFORM_WINDOWS
#if PLATFORM_64BITS
	FString RootPath = FPaths::GamePluginsDir() / TEXT("Flathead/ThirdParty/Flathead/Libraries/Windows/x64/Release/");
	FPlatformProcess::PushDllDirectory(*RootPath);
	FlatheadDLLHandle = FPlatformProcess::GetDllHandle(*(RootPath + "FlatheadCore.dll"));
	FPlatformProcess::PopDllDirectory(*RootPath);
#else
	FString RootSteamPath = FPaths::GamePluginsDir() / TEXT("Flathead/ThirdParty/Flathead/Libraries/Windows/x86/Release/");
	FPlatformProcess::PushDllDirectory(*RootSteamPath);
	FlatheadDLLHandle = FPlatformProcess::GetDllHandle(*(RootSteamPath + "FlatheadCore.dll"));
	FPlatformProcess::PopDllDirectory(*RootSteamPath);
#endif
#elif PLATFORM_MAC
	SteamDLLHandle = FPlatformProcess::GetDllHandle(TEXT("libsteam_api.dylib"));
#endif	//PLATFORM_WINDOWS


	if (FlatheadDLLHandle == nullptr)
	{
		UE_LOG(LogFlathead, Warning, TEXT("Failed to load Steam library."));
		return 1;
	}

	return 0;
}

void FlatheadModule::ReleaseFHDLL()
{

	if (FlatheadDLLHandle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(FlatheadDLLHandle);
		FlatheadDLLHandle = nullptr;
	}
}