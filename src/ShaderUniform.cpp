#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

namespace glb {

    // Specialization for float
    template <>
    inline void Shader::SetUniformVec1<float>(const std::string& name, const float& v0) {
        Bind();
        glUniform1f(GetUniformLocation(name), v0);
    }

    template <>
    void Shader::SetUniformVec2<float>(const std::string& name, const float& v0, const float& v1) {
        Bind();
        glUniform2f(GetUniformLocation(name), v0, v1);
    }

    template <>
    void Shader::SetUniformVec3<float>(const std::string& name, const float& v0, const float& v1, const float& v2) {
        Bind();
        glUniform3f(GetUniformLocation(name), v0, v1, v2);
    }

    template <>
    void Shader::SetUniformVec4<float>(const std::string& name, const float& v0, const float& v1, const float& v2, const float& v3) {
        Bind();
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }

    template <>
    void Shader::SetUniformVec1Array<float>(const std::string& name, int count, const float* value) {
        Bind();
        glUniform1fv(GetUniformLocation(name), count, value);
    }

    template <>
    void Shader::SetUniformVec2Array<float>(const std::string& name, int count, const float* value) {
        Bind();
        glUniform2fv(GetUniformLocation(name), count, value);
    }

    template <>
    void Shader::SetUniformVec3Array<float>(const std::string& name, int count, const float* value) {
        Bind();
        glUniform3fv(GetUniformLocation(name), count, value);
    }

    template <>
    void Shader::SetUniformVec4Array<float>(const std::string& name, int count, const float* value) {
        Bind();
        glUniform4fv(GetUniformLocation(name), count, value);
    }

    // Specialization for int
    template <>
    void Shader::SetUniformVec1<int>(const std::string& name, const int& v0) {
        Bind();
        glUniform1i(GetUniformLocation(name), v0);
    }

    template <>
    void Shader::SetUniformVec2<int>(const std::string& name, const int& v0, const int& v1) {
        Bind();
        glUniform2i(GetUniformLocation(name), v0, v1);
    }

    template <>
    void Shader::SetUniformVec3<int>(const std::string& name, const int& v0, const int& v1, const int& v2) {
        Bind();
        glUniform3i(GetUniformLocation(name), v0, v1, v2);
    }

    template <>
    void Shader::SetUniformVec4<int>(const std::string& name, const int& v0, const int& v1, const int& v2, const int& v3) {
        Bind();
        glUniform4i(GetUniformLocation(name), v0, v1, v2, v3);
    }

    template <>
    void Shader::SetUniformVec1Array<int>(const std::string& name, int count, const int* value) {
        Bind();
        glUniform1iv(GetUniformLocation(name), count, value);
    }

    template <>
    void Shader::SetUniformVec2Array<int>(const std::string& name, int count, const int* value) {
        Bind();
        glUniform2iv(GetUniformLocation(name), count, value);
    }

    template <>
    void Shader::SetUniformVec3Array<int>(const std::string& name, int count, const int* value) {
        Bind();
        glUniform3iv(GetUniformLocation(name), count, value);
    }

    template <>
    void Shader::SetUniformVec4Array<int>(const std::string& name, int count, const int* value) {
        Bind();
        glUniform4iv(GetUniformLocation(name), count, value);
    }

    // Specialization for unsigned int
    template <>
    void Shader::SetUniformVec1<unsigned int>(const std::string& name, const unsigned int& v0) {
        Bind();
        glUniform1ui(GetUniformLocation(name), v0);
    }

    template <>
    void Shader::SetUniformVec2<unsigned int>(const std::string& name, const unsigned int& v0, const unsigned int& v1) {
        Bind();
        glUniform2ui(GetUniformLocation(name), v0, v1);
    }

    template <>
    void Shader::SetUniformVec3<unsigned int>(const std::string& name, const unsigned int& v0, const unsigned int& v1, const unsigned int& v2) {
        Bind();
        glUniform3ui(GetUniformLocation(name), v0, v1, v2);
    }

    template <>
    void Shader::SetUniformVec4<unsigned int>(const std::string& name, const unsigned int& v0, const unsigned int& v1, const unsigned int& v2, const unsigned int& v3) {
        Bind();
        glUniform4ui(GetUniformLocation(name), v0, v1, v2, v3);
    }

    template <>
    void Shader::SetUniformVec1Array<unsigned int>(const std::string& name, int count, const unsigned int* value) {
        Bind();
        glUniform1uiv(GetUniformLocation(name), count, value);
    }

    template <>
    void Shader::SetUniformVec2Array<unsigned int>(const std::string& name, int count, const unsigned int* value) {
        Bind();
        glUniform2uiv(GetUniformLocation(name), count, value);
    }

    template <>
    void Shader::SetUniformVec3Array<unsigned int>(const std::string& name, int count, const unsigned int* value) {
        Bind();
        glUniform3uiv(GetUniformLocation(name), count, value);
    }

    template <>
    void Shader::SetUniformVec4Array<unsigned int>(const std::string& name, int count, const unsigned int* value) {
        Bind();
        glUniform4uiv(GetUniformLocation(name), count, value);
    }

    // Specialization for 2x2 matrix (glm::mat2)
    template <>
    void Shader::SetUniformMatrix<glm::mat2>(const std::string& name, const glm::mat2& matrix) {
        Bind();
        glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    template <>
    void Shader::SetUniformMatrixArray<glm::mat2>(const std::string& name, int count, const glm::mat2* matrices) {
        Bind();
        glUniformMatrix2fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(matrices[0]));
    }

    // Specialization for 3x3 matrix (glm::mat3)
    template <>
    void Shader::SetUniformMatrix<glm::mat3>(const std::string& name, const glm::mat3& matrix) {
        Bind();
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    template <>
    void Shader::SetUniformMatrixArray<glm::mat3>(const std::string& name, int count, const glm::mat3* matrices) {
        Bind();
        glUniformMatrix3fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(matrices[0]));
    }

    // Specialization for 4x4 matrix (glm::mat4)
    template <>
    void Shader::SetUniformMatrix<glm::mat4>(const std::string& name, const glm::mat4& matrix) {
        Bind();
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    template <>
    void Shader::SetUniformMatrixArray<glm::mat4>(const std::string& name, int count, const glm::mat4* matrices) {
        Bind();
        glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(matrices[0]));
    }

    // Specialization for 2x3 matrix (glm::mat2x3)
    template <>
    void Shader::SetUniformMatrix<glm::mat2x3>(const std::string& name, const glm::mat2x3& matrix) {
        Bind();
        glUniformMatrix2x3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    template <>
    void Shader::SetUniformMatrixArray<glm::mat2x3>(const std::string& name, int count, const glm::mat2x3* matrices) {
        Bind();
        glUniformMatrix2x3fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(matrices[0]));
    }

    // Specialization for 3x2 matrix (glm::mat3x2)
    template <>
    void Shader::SetUniformMatrix<glm::mat3x2>(const std::string& name, const glm::mat3x2& matrix) {
        Bind();
        glUniformMatrix3x2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    template <>
    void Shader::SetUniformMatrixArray<glm::mat3x2>(const std::string& name, int count, const glm::mat3x2* matrices) {
        Bind();
        glUniformMatrix3x2fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(matrices[0]));
    }

    // Specialization for 2x4 matrix (glm::mat2x4)
    template <>
    void Shader::SetUniformMatrix<glm::mat2x4>(const std::string& name, const glm::mat2x4& matrix) {
        Bind();
        glUniformMatrix2x4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    template <>
    void Shader::SetUniformMatrixArray<glm::mat2x4>(const std::string& name, int count, const glm::mat2x4* matrices) {
        Bind();
        glUniformMatrix2x4fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(matrices[0]));
    }


    // Specialization for 4x2 matrix (glm::mat4x2)
    template <>
    void Shader::SetUniformMatrix<glm::mat4x2>(const std::string& name, const glm::mat4x2& matrix) {
        Bind();
        glUniformMatrix4x2fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    template <>
    void Shader::SetUniformMatrixArray<glm::mat4x2>(const std::string& name, int count, const glm::mat4x2* matrices) {
        Bind();
        glUniformMatrix4x2fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(matrices[0]));
    }

    // Specialization for 3x4 matrix (glm::mat3x4)
    template <>
    void Shader::SetUniformMatrix<glm::mat3x4>(const std::string& name, const glm::mat3x4& matrix) {
        Bind();
        glUniformMatrix3x4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    template <>
    void Shader::SetUniformMatrixArray<glm::mat3x4>(const std::string& name, int count, const glm::mat3x4* matrices) {
        Bind();
        glUniformMatrix3x4fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(matrices[0]));
    }

    // Specialization for 4x3 matrix (glm::mat4x3)
    template <>
    void Shader::SetUniformMatrix<glm::mat4x3>(const std::string& name, const glm::mat4x3& matrix) {
        Bind();
        glUniformMatrix4x3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    template <>
    void Shader::SetUniformMatrixArray<glm::mat4x3>(const std::string& name, int count, const glm::mat4x3* matrices) {
        Bind();
        glUniformMatrix4x3fv(GetUniformLocation(name), count, GL_FALSE, glm::value_ptr(matrices[0]));
    }

}