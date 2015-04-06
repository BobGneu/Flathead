
#include "../../ThirdParty/FlatheadCore/Include/Object.h"
#include "../../ThirdParty/FlatheadCore/Include/Result.h"
#include "../../ThirdParty/FlatheadCore/Include/Types.h"

class IFlathead : public IModuleInterface
{
public:
	virtual void ModuleTick() = 0;
	virtual bool Expose(char * name, Flathead::Object *obj) = 0;
	virtual void SetLoggingFunction(LoggingFunction) = 0;
	virtual void Execute(char* code, Flathead::Result *pResultOut) = 0;
};