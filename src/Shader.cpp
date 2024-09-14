#include "Shader.h"

#include <fstream>
#include <filesystem>

#include "Debug.h"

namespace glb {

    ShaderProgramSource ShaderProgramSource::ReadFromFile(const std::string& filepath)
    {
        std::ifstream stream(filepath);

        if (!stream.is_open())
        {
            GLBErrH(OpenFileFailed, "Failed to open the shader source file '" << filepath << "'");
            return { std::string(), std::string() };
        }

        enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
                else
                    GLBWarnH(UnknownType, "Unknown shader source type:\n" << line);
            }
            else
            {
                if (type != ShaderType::NONE)
                    ss[(int)type] << line << "\n";
                else
                    GLBWarnL(UnknownType, "Does not specify a shader type!");
            }
        }

        stream.close();

        return { ss[0].str(), ss[1].str() };
    }

    ShaderProgramSource ShaderProgramSource::ReadFromFile(const std::string& vertex, const std::string& fragment)
    {
        std::stringstream ss[2];
        std::ifstream stream;

        // Read vertex shader source 
        stream.open(vertex);

        if (!stream.is_open())
        {
            GLBErrH(OpenFileFailed, "Failed to open the vertex shader source file '" << vertex << "'");
            return { std::string(), std::string() };
        }

        ss[0] << stream.rdbuf();

        stream.close();

        // Read fragment shader source
        stream.open(fragment);

        if (!stream.is_open())
        {
            GLBErrH(OpenFileFailed, "Failed to open the fragment shader source file '" << fragment << "'");
            return { std::string(), std::string() };
        }

        ss[1] << stream.rdbuf();

        stream.close();

        return { ss[0].str(), ss[1].str() };
    }

    Shader::Shader(const ShaderProgramSource& source)
    {
        m_rendererID = CreateShader(source.VertexSource, source.FragmentSource);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_rendererID);
    }

    unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);
        return program;
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // Check error
        int res = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &res);
        if (res == GL_FALSE)
        {
            int length = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

            char* buffer = new char[length];
            glGetShaderInfoLog(id, length, &length, buffer);
            GLBErrH(ShaderCompiledFailed, "Failed to compile " <<
                (type == GL_VERTEX_SHADER ? "vertx" : "fragment") << "shader!");
            GLBSay(buffer);
            delete[] buffer;
        }

        return id;
    }

    int Shader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformLocationCoach.find(name) != m_UniformLocationCoach.end())
            return m_UniformLocationCoach[name];

        int location = glGetUniformLocation(m_rendererID, name.c_str());
        if (location == -1)
            GLBWarnH(UnknownUniform, "Uniform '" << name << "' doesn't exist!");

        m_UniformLocationCoach[name] = location;
        return location;
    }

}