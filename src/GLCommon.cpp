#include "GLCommon.h"

namespace glb {

    void ClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    bool LogCall(const char* function, const char* file, int line)
    {
        while (GLenum error = glGetError())
        {
            std::cerr << "[OpenGL Error] (" << error << "): " << function <<
                " " << file << " : " << line << std::endl;
            GLDebugbreak();
            return false;
        }
        return true;
    }

}
