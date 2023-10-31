#ifndef TUNKS_SHADER_HPP
#define TUNKS_SHADER_HPP

#include "Defines.hpp"
#include <GL/glew.h>
#include <string>


class Shader {
public:
    Shader(const std::string& vertexShaderPath,const std::string& fragmentShader);

    virtual ~Shader();

    void bind();
    void unbind();
private:
    GLuint m_shaderId;
    GLuint createShader(const std::string& vertexShaderPath,const std::string& fragmentShader);
    GLuint compile(const std::string &shaderContent,GLenum type);
    std::string readShaderFromFile(const std::string& path);
};


#endif
