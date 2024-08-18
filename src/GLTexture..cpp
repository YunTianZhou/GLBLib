#include "GLTexture.h"

#include <stb_image/stb_image.h>

namespace glb {
	Texture::Texture(const std::string& filepath)
		: m_rendererID(0), m_filepath(filepath), m_localBuffer(nullptr),
		  m_width(0), m_height(0), m_BPP(0)
	{
		// Set the coordinate origin to the bottom left
		stbi_set_flip_vertically_on_load(1);

		// Load the image form the specify file
		m_localBuffer = stbi_load(m_filepath.c_str(), &m_width, &m_height, &m_BPP, 4);

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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);

		// Unbind the texture
		glBindTexture(GL_TEXTURE_2D, 0);

		// Free the local buffer
		if (m_localBuffer)
			stbi_image_free(m_localBuffer);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_rendererID);
	}
}