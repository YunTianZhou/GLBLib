#pragma once

#include <string>
#include <vector>

#include "Export.h"

struct GLFWimage;

namespace glb {

	class GLB_API Image
	{
	public:
		Image();
        Image(int width, int height, const unsigned char* pixels);
		explicit Image(const std::string& filepath);

		Image(Image&& other) noexcept;
		Image& operator=(Image&& other) noexcept;

		Image(const Image&) noexcept;
		Image& operator=(const Image&) noexcept;

		bool LoadFromFile(const std::string& filepath);
		bool SaveToFile(const std::string& filepath);

		void FlipHorizontally();
		void FlipVertically();

		inline int GetWidth() const { return m_width; };
		inline int GetHeight() const { return m_height; };
		inline int IsExist() const { return m_width && m_height && !m_pixels.empty(); };
		inline std::vector <unsigned char>& GetPixels() { return m_pixels; };
		inline const std::vector <unsigned char>& GetPixels() const { return m_pixels; };

		inline void Free();

	public:
		inline static void Free(Image& image);
		inline static void Free(Image images[], int size);

	private:
		friend class Window;
		GLFWimage GetGLFWimage();

	private:
		int m_width;
		int m_height;
		std::vector <unsigned char> m_pixels;
	};

	inline void Image::Free()
	{
		m_pixels.clear();
		m_pixels.shrink_to_fit();
	}

	inline void Image::Free(Image& image)
	{
		image.Free();
	}

	inline void Image::Free(Image images[], int size)
	{
		for (int i = 0; i < size; i++)
			images[i].Free();
	}


}