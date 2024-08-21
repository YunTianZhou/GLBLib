#include "Common.h"

namespace glb {

	class GLB_API CursorCallback
	{
	public:
		void* Position = nullptr;
		void* Enter = nullptr;
		void* MouseButton = nullptr;
		void* Scroll = nullptr;
	};

	class GLB_API KeyCallback
	{
	public:
		void* Key = nullptr;
		void* Char = nullptr;
	};

	class GLB_API CallbackManager
	{
	public:
		CursorCallback Cursor;
		KeyCallback Key;
	};

	extern CallbackManager Manager;

}