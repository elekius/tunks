#ifndef TUNKS_SHADER_HPP
#define TUNKS_SHADER_HPP
#include <glad/glad.h>
#include "../Defines.hpp"
#include "glm/glm.hpp"
#include <string>
#include <map>
#include <unordered_map>

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
    GLint getUniformLocation(const std::string &name);
    void setUniformMatrix4fv(const std::string &name, const glm::mat4 &value);
    void setUniformVec3(const std::string &name, const glm::vec3 &value);
    void setUniformFloat(const std::string &name, const float &value);
    void setUniformInt(const std::string &name, const int &value);


private:
    GLuint m_shaderId;
    std::unordered_map<std::string,GLint> m_cachedUniforms;

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
