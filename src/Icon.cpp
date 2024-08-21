#include "Icon.h"

#include <stb_image/stb_image.h>

namespace glb {

	Icon::Icon(const std::string& filepath)
		: m_width(0), m_height(0), m_pixels(nullptr)
	{
		// Load the image form the specify file
		int channels;
		m_pixels = stbi_load(filepath.c_str(), &m_width, &m_height, &channels, 4);
		if (!m_pixels)
			GLError("Loard icon faild from file '" << filepath << "'");
	}
	Icon::Icon(int width, int height, unsigned char* pixels)
		: m_width(width), m_height(height), m_pixels(pixels)
	{
	}

	Icon::Icon(Icon&& other) noexcept
	{
		if (!other.m_pixels)
		{
			GLWarn("Move a non-exist icon!");
		}

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
		GLLog("Copy icon!");
		if (other.m_pixels)
		{
			m_pixels = new unsigned char[m_width * m_height * 4];
			std::memcpy(m_pixels, other.m_pixels, m_width * m_height * 4);
		}
		else
		{
			GLWarn("Copy a non-exist icon!");
		}
	}
	Icon& Icon::operator=(const Icon& other) noexcept
	{
		if (this == &other)
			return *this;

		GLLog("Copy icon!");

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
			GLWarn("Copy a non-exist icon!");
			m_pixels = nullptr;
		}

		return *this;
	}


	void Icon::Free()
	{
		if (!m_pixels)
		{
			GLWarn("Icon is already free!");
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
			GLWarn("Icon does not exist!");
			return { 0, 0, nullptr };
		}
		return { m_width, m_height, m_pixels };
	}

}