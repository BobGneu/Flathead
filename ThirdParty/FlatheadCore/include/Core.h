#pragma once

#include "API.h"
#include "Configuration.h"
#include "ICore.h"
#include "Result.h"
#include "Object.h"
#include "Types.h"

namespace Flathead
{

	/// Entry to the plugin. This is where we have the initialization and such handled. 
	/// ToDo: Configuration object can be used to pass in different engines which can be loaded from dlls if so chosen. 
	class FH_API Core : public ICore
	{
	public:
		bool Initialized; 

		Core();
		Core(Configuration &configuration);
		Core(Configuration &configuration, LoggingFunction fn);
		~Core();

		void AllowHotReload(bool);
		bool AllowHotReload();

		void Path(const char *);
		const char *Path();

		void Initialize();
		void Shutdown();

		void ModuleTick();

		bool Expose(char * name, Object *obj);

		void SetLoggingFunction(LoggingFunction);

		void Execute(char* code, Result *pResultOut);

	private:
		void ProcessConfigurationObject(Configuration &configuration);

		void SetupDefaults();
		LoggingFunction fnLog;

		char path[2048];
		bool allowHotReload;
	};
};