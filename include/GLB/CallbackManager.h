#include "Export.h"

namespace glb {

	class GLB_API WindowCallback
	{
	public:
		void* Close = nullptr;
		void* Size = nullptr;
		void* FramebufferSize = nullptr;
		void* Position = nullptr;
		void* Iconify = nullptr;
		void* Maximize = nullptr;
		void* Focus = nullptr;
		void* Refresh = nullptr;
	};

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
		WindowCallback Window;
		CursorCallback Cursor;
		KeyCallback Key;
	};

	extern CallbackManager Manager;

}