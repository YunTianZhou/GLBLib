#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

#include "Export.h"

namespace glb {

    class GLB_API ShaderProgramSource
    {
    public:
        std::string VertexSource;
        std::string FragmentSource;

        /*
            Read the shader source from a file with a basic format:
            ____________________________________________________________

            #shader vertex

            ...( vertex shader source )

            #shader fragment

            ...( fragment shader source )

            ____________________________________________________________
        */
        static ShaderProgramSource ReadFromFile(const std::string& filepath);

        // Read the shader source from two files
        static ShaderProgramSource ReadFromFile(const std::string& vertex, const std::string& fragment);
    };

    class GLB_API Shader
    {
    public:
        explicit Shader(const ShaderProgramSource& source);

        ~Shader();

        inline void Bind() const { glUseProgram(m_rendererID); }
        inline void Unbind() const { glUseProgram(0); }

        template <class T> void SetUniformVec1(const std::string& name, const T& v0);
        template <class T> void SetUniformVec2(const std::string& name, const T& v0, const T& v1);
        template <class T> void SetUniformVec3(const std::string& name, const T& v0, const T& v1, const T& v2);
        template <class T> void SetUniformVec4(const std::string& name, const T& v0, const T& v1, const T& v2, const T& v3);

        template <class T> void SetUniformVec1Array(const std::string& name, int count, const T* value);
        template <class T> void SetUniformVec2Array(const std::string& name, int count, const T* value);
        template <class T> void SetUniformVec3Array(const std::string& name, int count, const T* value);
        template <class T> void SetUniformVec4Array(const std::string& name, int count, const T* value);

        template <class T> void SetUniformMatrix(const std::string& name, const T& matrix);
        template <class T> void SetUniformMatrixArray(const std::string& name, int count, const T* matrices);

    private:
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

        unsigned int CompileShader(unsigned int type, const std::string& source);

        int GetUniformLocation(const std::string& name);
    private:
        unsigned int m_rendererID;
        std::unordered_map<std::string, int> m_UniformLocationCoche;
    };

}