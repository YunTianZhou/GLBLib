#pragma once

#include "Common.h"

namespace glb {

	class GLB_API Texture
	{
	public:
		Texture(const std::string& filepath);

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
		std::string m_filepath;
		unsigned char* m_localBuffer;
		int m_width, m_height, m_BPP;
	};

}