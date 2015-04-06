#include "FlatheadPCH.h"
#include "Flathead_impl.h"

#include "FlatheadCore/include/Core.h"

DEFINE_LOG_CATEGORY(LogFlathead);

void FlatheadImpl::StartupModule()
{
	Flathead::Configuration cfg;
	FString path = FPaths::GamePluginsDir();
	path = path / "Flathead" / "Scripts";
	UE_LOG(LogFlathead, Display, TEXT("%s"), *path);
	cfg.Path(TCHAR_TO_ANSI(*path));
	pCore = new Flathead::Core(cfg);

	pCore->SetLoggingFunction(FlatheadImpl::LoggingMessage);

	pCore->Initialize();

	pCore->Execute("require('core');", NULL);
}

void FlatheadImpl::LoggingMessage(int type, const char *message)
{
	UE_LOG(LogFlathead, Display, TEXT("%d - %s"), type, ANSI_TO_TCHAR(message));
}

void FlatheadImpl::ShutdownModule()
{
	if (pCore != nullptr)
	{
		delete pCore;
	}
}

void FlatheadImpl::ModuleTick()
{
	pCore->ModuleTick();
}

bool FlatheadImpl::Expose(char * name, Flathead::Object *obj)
{
	return pCore->Expose(name, obj);
}

void FlatheadImpl::SetLoggingFunction(LoggingFunction fn)
{
	pCore->SetLoggingFunction(fn);
}

void FlatheadImpl::Execute(char* code, Flathead::Result *pResultOut)
{
	pCore->Execute(code, pResultOut);
}