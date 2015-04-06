
#include "Public/IFlathead.h"
#include "../../ThirdParty/FlatheadCore/Include/Core.h"

class FlatheadImpl : public IFlathead
{
	virtual void StartupModule();
	virtual void ShutdownModule();

	virtual void ModuleTick();

	virtual bool Expose(char * name, Flathead::Object *obj);

	virtual void SetLoggingFunction(LoggingFunction);

	virtual void Execute(char* code, Flathead::Result *pResultOut);

	Flathead::Core *pCore;

	static void LoggingMessage(int type, const char *message);
};

IMPLEMENT_MODULE(FlatheadImpl, Flathead);