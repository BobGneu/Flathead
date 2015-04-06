
#ifdef _Exporting
	#define FH_API	__declspec(dllexport)
#else
	#define FH_API  __declspec(dllimport)
#endif
