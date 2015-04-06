#pragma once

#include "API.h"

namespace Flathead
{
	class FH_API Configuration
	{
	public:
		Configuration();

		void Path(const char *);
		const char *Path();

		void AllowHotReload(bool);
		bool AllowHotReload();

	private:
		char path[2048];
		bool allowHotReload;
	};
}
