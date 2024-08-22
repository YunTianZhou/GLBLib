#ifdef _WIN32
	#ifdef GLB_EXPORTS
		#define GLB_API __declspec(dllexport)
	#else
		#define GLB_API __declspec(dllimport)
	#endif
#else
	#define GLB_API
#endif