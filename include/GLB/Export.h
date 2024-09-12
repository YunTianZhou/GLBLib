#ifndef GLB_STATIC
	#if defined(_WIN32)
		#ifdef GLB_EXPORTS
			#define GLB_API __declspec(dllexport)
		#else
			#define GLB_API __declspec(dllimport)
		#endif
	#elif defined(__GNUC__)
		#define GLB_API __attribute__((visibility("default")))
	#endif
#endif

#ifndef GLB_API
	#define GLB_API
#endif