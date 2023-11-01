#ifndef TUNKS_SHADER_HPP
#define TUNKS_SHADER_HPP

#include "Defines.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>


class Shader {
public:
    Shader(const std::string& vertexShaderPath,const std::string& fragmentShader);

    virtual ~Shader();
    void bind();
    void unbind();
    GLuint getShaderId() const;

    void setUniformMatrix4fv(const std::string& name, const glm::mat4 &value);


private:
    GLuint m_shaderId;
    GLuint createShader(const std::string& vertexShaderPath,const std::string& fragmentShader);
    GLuint compile(const std::string &shaderContent,GLenum type);
    std::string readShaderFromFile(const std::string& path);
};


#endif
