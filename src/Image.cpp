#include "Image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <filesystem>
#include <stb_image.h>
#include <stb_image_write.h>

#include "Debug.h"

namespace glb {

	Image::Image()
		: m_width(0), m_height(0)
	{
	}

	Image::Image(int width, int height, const unsigned char* pixels)
		: m_width(width), m_height(height)
	{
		if (IsExist())
		{
			std::vector<unsigned char> newPixels(pixels, pixels + width * height * 4);
			m_pixels.swap(newPixels);
			return;
		}
		GLBWarnL(ObjectNonExist, "The image is not exist!");
	}

	Image::Image(const std::string& filepath)
		: m_width(0), m_height(0)
	{
		LoadFromFile(filepath);
	}

	Image::Image(Image&& other) noexcept
		: m_width(other.m_width), m_height(other.m_height)
	{
		GLBAssertWL(other.IsExist(), ObjectNonExist, "Move a non-exist icon!");

		m_pixels.swap(other.m_pixels);
	}

	Image& Image::operator=(Image&& other) noexcept
	{
		m_width = other.m_width;
		m_height = other.m_height;
		m_pixels.swap(other.m_pixels);

		other.Free();

		return *this;
	}

	Image::Image(const Image& other) noexcept
		: m_width(other.m_width), m_height(other.m_height), m_pixels(other.m_pixels)
	{
		GLBWarnL(CopyImage, "Copy image!");
		GLBAssertWL(other.IsExist(), ObjectNonExist, "Copy a non-exist icb on!");
	}

	Image& Image::operator=(const Image& other) noexcept
	{
		if (this == &other)
			return *this;

		GLBWarnL(CopyImage, "Copy image!");

		if (other.IsExist())
		{
			m_width = other.m_width;
			m_height = other.m_height;
			m_pixels = other.m_pixels;
		}
		else
		{
			GLBWarnL(ObjectNonExist, "Copy a non-exist icon!");
			Free();
		}

		return *this;
	}

	bool Image::LoadFromFile(const std::string& filepath)
	{
		// Set the coordinate origin to the bottom left
		stbi_set_flip_vertically_on_load(0);

		// Load the image form the specify file
		int width = 0, height = 0, channels = 0;
		const unsigned char* buffer = stbi_load(filepath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

		if (buffer)
		{
			m_width = width, m_height = height;
			m_pixels.assign(buffer, buffer + width * height * 4);
			return true;
		}

		GLBErrL(LoadImageFaild, "Faild to load image from file '" << filepath << "'");
		return false;
	}

	bool Image::SaveToFile(const std::string& filepath)
	{
		if (!m_pixels.empty() && m_width > 0 && m_height > 0)
		{
			std::filesystem::path extension = std::filesystem::path(filepath).extension();

			if (extension == ".bmp")
			{
				// BMP format
				if (stbi_write_bmp(filepath.c_str(), m_width, m_height, 4, m_pixels.data()))
					return true;
			}
			else if (extension == ".tga")
			{
				// TGA format
				if (stbi_write_tga(filepath.c_str(), m_width, m_height, 4, m_pixels.data()))
					return true;
			}
			else if (extension == ".png")
			{
				// PNG format
				if (stbi_write_png(filepath.c_str(), m_width, m_height, 4, m_pixels.data(), 0))
					return true;
			}
			else if (extension == ".jpg" || extension == ".jpeg")
			{
				// JPG format
				if (stbi_write_jpg(filepath.c_str(), m_width, m_height, 4, m_pixels.data(), 90))
					return true;
			}
			else
			{
				GLBErrL(UnknowType, "Image file extension " << extension << " not supported!");
			}
		}

		GLBErrL(SaveImageFaild, "Failed to save image!");
		return false;
	}

	void Image::FlipHorizontally()
	{
		if (!m_pixels.empty())
		{
			using iterator = std::vector<unsigned char>::iterator;

			int rowSize = m_width * 4;

			for (int y = 0; y < m_height; y++)
			{
				iterator left = m_pixels.begin() + (iterator::difference_type)(y * rowSize);
				iterator right = m_pixels.begin() + (iterator::difference_type)((y + 1) * rowSize - 4);

				for (int x = 0; x < m_width / 2; x++)
				{
					std::swap_ranges(left, left + 4, right);

					left += 4;
					right -= 4;
				}
			}
		}
		else
		{
			GLBWarnL(ObjectNonExist, "The image is not exist!");
		}
	}

	void Image::FlipVertically()
	{
		if (!m_pixels.empty())
		{
			using iterator = std::vector<unsigned char>::iterator;

			iterator::difference_type rowSize = (iterator::difference_type) (m_width * 4);

			iterator top = m_pixels.begin();
			iterator bottom = m_pixels.end() - rowSize;

			for (std::size_t y = 0; y < m_height / 2; y++)
			{
				std::swap_ranges(top, top + rowSize, bottom);

				top += rowSize;
				bottom -= rowSize;
			}
		}
		else
		{
			GLBWarnL(ObjectNonExist, "The image is not exist!");
		}
	}

	GLFWimage Image::GetGLFWimage()
	{
		if (!m_width || !m_height || m_pixels.empty())
		{
			GLBWarnL(ObjectNonExist, "Icon does not exist!");
			return { 0, 0, nullptr };
		}
		return { m_width, m_height, m_pixels.data() };
	}

}