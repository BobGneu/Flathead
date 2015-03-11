#pragma once

// #include "../inc/IFlathead.h"

#ifdef _Exporting
#define FH_API    __declspec(dllexport)
#else
#define FH_API    __declspec(dllimport)
#endif

namespace FH
{
	class FH_API FlatheadCore // : public IFlathead
	{
	public:
		bool Initialized;

		FlatheadCore();
		~FlatheadCore();

		void Initialize();
		void Shutdown();
	};
};