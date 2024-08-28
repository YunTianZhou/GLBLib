#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"

namespace glb {

	class VertexArray;
	class IndexBuffer;
	class Shader;

	class GLB_API Renderer
	{
	public:
		enum class Mode
		{
			Points = GL_POINTS,
			LineStrip = GL_LINE_STRIP,
			LineLoop = GL_LINE_LOOP,
			Lines = GL_LINES,
			LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
			LinesAdjacency = GL_LINES_ADJACENCY,
			TriangleStrip = GL_TRIANGLE_STRIP,
			TriangleFan = GL_TRIANGLE_FAN,
			Triangles = GL_TRIANGLES,
			TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
			TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
			Patches = GL_PATCHES,
		};
	private:
		Renderer() = delete;
	public:
		static void Clear();
		static void SetClearColor(float r, float g, float b, float a);
		static void SetViewport(int x, int y, int width, int height);

		static void DrawArray(Mode mode, const VertexArray& va, const Shader& shader, unsigned int first, unsigned int count);
		static void DrawElements(Mode mode, const VertexArray& va, const IndexBuffer& ib, const Shader& shader, int count = -1, unsigned int first = 0);
	};

}