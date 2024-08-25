#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Export.h"

namespace glb {

	class Image;

	class GLB_API Texture
	{
	private:
		void Init(const unsigned char* buffer);
	public:
		Texture(const std::string& filepath);
		Texture(int width, int height, unsigned char* buffer);
		Texture(const Image& image);

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		~Texture();

		inline void Bind(unsigned int slot = 0) const
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_rendererID);
		}

		inline void Unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }

	private:
		unsigned int m_rendererID;
		int m_width, m_height;
	};

}