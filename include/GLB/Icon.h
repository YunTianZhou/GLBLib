#pragma once

#include <string>

#include "Export.h"

struct GLFWimage;

namespace glb {

	class GLB_API Icon
	{
	private:
		friend class Window;
	public:
		Icon(const std::string& filepath);
		Icon(int width, int height, unsigned char* pixels);

		Icon(Icon&& other) noexcept;
		Icon& operator=(Icon&& other) noexcept;

		Icon(const Icon&) noexcept;
		Icon& operator=(const Icon&) noexcept;

		void Free();
		~Icon();

		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }
		inline bool IsExist() const { return m_pixels != nullptr; }
	public:
		inline static void Free(Icon& icon)
		{
			icon.Free();
		}

		inline static void Free(Icon icons[], int size)
		{
			for (int i = 0; i < size; i++)
				icons[i].Free();
		}
	private:
		GLFWimage GetImage() const;

	private:
		int m_width, m_height;
		unsigned char* m_pixels;
	};

}