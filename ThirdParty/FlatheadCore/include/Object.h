#pragma once

#include "API.h"
#include "Types.h"

namespace Flathead
{
	class FH_API Object
	{
	public:
		// Standard Property types
		void Set(char *key, const char *value);
		void Set(char *key, int value);
		void Set(char *key, double value);
		void Set(char *key, bool value);

		// Method binding
		void Set(char *key, IntCallback value);
		void Set(char *key, VoidCallback value);
		void Set(char *key, BoolCallback value);
		void Set(char *key, StringCallback value);
		void Set(char *key, NumberCallback value);

		void SetHandler(void *handler);
		void SetInternal(void *obj);
		
		const char * GetName() const;
		void SetName(const char *name);

		void Bind(void *obj);
		void *External();

	private:
		char *Name;
		void *Handler;
		void *Internal;
	};
}