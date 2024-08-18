#pragma once

#include "GLCommon.h"

namespace glb {

	class VertexArray;
	class IndexBuffer;
	class Shader;

	class GLB_API Renderer
	{
	private:
		Renderer();
	public:
		static void Clear();
		static void DrawArray(const VertexArray& va, const Shader& shader, unsigned int first, unsigned int count);
		static void DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, int count = -1, unsigned int first = 0);
	
		static void SetClearColor(float r, float g, float b, float a);
	};

}