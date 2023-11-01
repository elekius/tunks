#ifndef TUNKS_SHADER_HPP
#define TUNKS_SHADER_HPP

#include "Defines.hpp"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <string>

/**
 * A simple Wrapper for a shader program.
 * @author ChikyuKido
 */
class Shader {
public:
    /**
     * Creates a new shader with the given vert and frag shader
     * @param vertexShaderPath the path to the vertex shader
     * @param fragmentShader the path to the fragment shader
     */
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShader);

    virtual ~Shader();

    /**
     * Binds the shader.
     */
    void bind();
    /**
     * unbind the shader
     */
    void unbind();
    /**
     * Returns the shaderId
     * @return
     */
    [[nodiscard]] GLuint getShaderId() const;

    /**
     * Sets a matrix4 uniform for the shader
     * @param name the name of the uniform
     * @param value the value for the uniform
     */
    void setUniformMatrix4fv(const std::string &name, const glm::mat4 &value);


private:
    GLuint m_shaderId;

    /**
     * Compiles the two shaders and create a single shader program.
     * @param vertexShaderPath the path to the vertex shader
     * @param fragmentShader the path to the fragment shader
     * @return a opengl id for the shader program
     */
    GLuint createShader(const std::string &vertexShaderPath, const std::string &fragmentShader);

    /**
     * Compiles a vertex or fragment shader.
     * @param shaderContent The shader source code
     * @param type the type fragment or vertex shader
     * @return a opengl id for a shader
     */
    GLuint compile(const std::string &shaderContent, GLenum type);

    /**
     * Reads the content of the path
     * @param path the file with the shader contents
     * @return the content of the file
     */
    std::string readStringFromFile(const std::string &path);
};


#endif
