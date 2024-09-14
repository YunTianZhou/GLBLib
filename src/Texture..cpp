#include "Texture.h"

#include <stb/stb_image.h>
#include "Image.h"
#include "Debug.h"

namespace glb {
	void Texture::Init(const unsigned char* buffer)
	{
		// Gen the texture and bind it
		glGenTextures(1, &m_rendererID);
		glBindTexture(GL_TEXTURE_2D, m_rendererID);

		// Set the parameteri (settings) of the texture
		// Set the texture minifying function to linear interpolation
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Set the texture magnification function to linear interpolation
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set the texture wrapping mode for the S (x) axis to clamp to edge
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		// Set the texture wrapping mode for the T (y) axis to clamp to edge
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Bind the image buffer to the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		// Unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::Texture(const std::string& filepath)
		: m_rendererID(0), m_width(0), m_height(0)
	{
		// Set the coordinate origin to the bottom left
		stbi_set_flip_vertically_on_load(1);

		// Load the image form the specify file
		int channel = 0; 
		unsigned char* buffer = stbi_load(filepath.c_str(), &m_width, &m_height, &channel, STBI_rgb_alpha);

		// Init the GL Texture
		Init(buffer);

		// Free the local buffer
		if (buffer)
			stbi_image_free(buffer);
		else
			GLBErrL(LoadImageFailed, "Failed to load texture from file '" << filepath << "'");
	}

	Texture::Texture(int width, int height, unsigned char* buffer)
		: m_rendererID(0), m_width(width), m_height(height)
	{
		// Init the OpenGL Texture based on the given buffer
		Init(buffer);
	}

	Texture::Texture(const Image& image)
		: m_rendererID(0), m_width(image.GetWidth()), m_height(image.GetHeight())
	{
		// Init the OpenGL Texture based on the given image
		Init(image.GetPixels().data());
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_rendererID);
	}
}