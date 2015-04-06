#pragma once;

#include "API.h"

namespace Flathead
{
	class FH_API Function
	{
	public:
		Function();
		~Function();

		void SetStringRepresentation(char *value, int length);

		char *StringRepresentation;
	};
}