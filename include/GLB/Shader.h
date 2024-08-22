#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

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
    };

    class GLB_API Shader
    {
    public:
        Shader(const ShaderProgramSource& source);

        ~Shader();

        inline void Bind() const { glUseProgram(m_rendererID); }
        inline void Unbind() const { glUseProgram(0); }

        void SetUniform1i(const std::string name, int value);

        void SetUniform1f(const std::string name, float value);

        void SetUniform2f(const std::string name, float v0, float v1);

        void SetUniform4f(const std::string name, float v0, float v1, float v2, float v3);

        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

    private:
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

        unsigned int CompileShader(unsigned int type, const std::string& source);

        int GetUniformLocation(const std::string& name);
    private:
        unsigned int m_rendererID;
        std::unordered_map<std::string, int> m_UniformLocationCoche;
    };

}