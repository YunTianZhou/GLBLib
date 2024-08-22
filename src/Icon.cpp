#include "Icon.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include "Debug.h"


namespace glb {

	Icon::Icon(const std::string& filepath)
		: m_width(0), m_height(0), m_pixels(nullptr)
	{
		// Set the coordinate origin to the bottom left
		stbi_set_flip_vertically_on_load(0);

		// Load the image form the specify file
		int channels;
		m_pixels = stbi_load(filepath.c_str(), &m_width, &m_height, &channels, 4);
		GLBAssertEL(m_pixels, LoadImageFaild, "Loard icon faild from file '" << filepath << "'");
	}

	Icon::Icon(int width, int height, unsigned char* pixels)
		: m_width(width), m_height(height), m_pixels(pixels)
	{
	}

	Icon::Icon(Icon&& other) noexcept
	{
		GLBAssertWL(other.m_pixels, ObjectNonExist, "Move a non-exist icon!");

		m_width = other.m_width;
		m_height = other.m_height;
		m_pixels = other.m_pixels;

		other.m_pixels = nullptr;
	}
	Icon& Icon::operator=(Icon&& other) noexcept
	{
		if (m_pixels)
			Free();

		m_width = other.m_width;
		m_height = other.m_height;
		m_pixels = other.m_pixels;

		other.m_width = 0;
		other.m_height = 0;
		other.m_pixels = nullptr;

		return *this;
	}

	Icon::Icon(const Icon& other) noexcept
		: m_width(other.m_width), m_height(other.m_height), m_pixels(nullptr)
	{
		GLBWarnL(CopyLargeMemory, "Copy icon!");
		if (other.m_pixels)
		{
			m_pixels = new unsigned char[m_width * m_height * 4];
			std::memcpy(m_pixels, other.m_pixels, m_width * m_height * 4);
		}
		else
		{
			GLBWarnL(ObjectNonExist, "Copy a non-exist icon!");
		}
	}
	Icon& Icon::operator=(const Icon& other) noexcept
	{
		if (this == &other)
			return *this;

		GLBWarnL(CopyLargeMemory, "Copy icon!");

		if (m_pixels)
			Free();

		m_width = other.m_width;
		m_height = other.m_height;

		if (other.m_pixels)
		{
			m_pixels = new unsigned char[m_width * m_height * 4];
			std::memcpy(m_pixels, other.m_pixels, m_width * m_height * 4);
		}
		else
		{
			GLBWarnL(ObjectNonExist, "Copy a non-exist icon!");
			m_pixels = nullptr;
		}

		return *this;
	}


	void Icon::Free()
	{
		if (!m_pixels)
		{
			GLBWarnL(DoubleFree, "Icon is already free!");
			return;
		}
		stbi_image_free(m_pixels);
		m_width = 0;
		m_height = 0;
		m_pixels = nullptr;
	}
	Icon::~Icon()
	{
		if (m_pixels)
			Free();
	}

	GLFWimage Icon::GetImage() const
	{
		if (!m_pixels)
		{
			GLBWarnL(ObjectNonExist, "Icon does not exist!");
			return { 0, 0, nullptr };
		}
		return { m_width, m_height, m_pixels };
	}

}