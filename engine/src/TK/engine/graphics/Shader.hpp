#ifndef TUNKS_SHADER_HPP
#define TUNKS_SHADER_HPP
#include <glad/glad.h>
#include "../Defines.hpp"
#include "glm/glm.hpp"
#include <string>
#include <map>
#include <unordered_map>

/**
 * @brief A simple Wrapper for a shader program.
 *
 * This class provides a simple wrapper for managing shader programs, including loading shaders,
 * setting uniform values, and binding/unbinding the shader program.
 * @author ChikyuKido
 */
class Shader {
public:
    /**
     * @brief Creates a new shader with the given vertex and fragment shaders.
     *
     * @param vertexShaderPath The path to the vertex shader source file.
     * @param fragmentShaderPath The path to the fragment shader source file.
     */
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    virtual ~Shader();

    /**
     * @brief Binds the shader program for use in rendering.
     */
    void bind();

    /**
     * @brief Unbinds the shader program.
     */
    void unbind();

    [[nodiscard]] GLuint getShaderId() const;

    /**
     * @brief Get the location of a uniform variable in the shader.
     *
     * @param name The name of the uniform variable.
     * @return The location of the uniform variable.
     */
    GLint getUniformLocation(const std::string &name);
    void setUniformMatrix4fv(const std::string &name, const glm::mat4 &value);
    void setUniformVec3(const std::string &name, const glm::vec3 &value);
    void setUniformFloat(const std::string &name, const float &value);
    void setUniformInt(const std::string &name, const int &value);
    void setUniformBool(const std::string &name, const bool &value);

private:
    GLuint m_shaderId; // The OpenGL shader program ID.
    std::unordered_map<std::string, GLint> m_cachedUniforms; // Cache for uniform variable locations.

    /**
     * @brief Compiles the two shaders and creates a single shader program.
     *
     * @param vertexShaderPath The path to the vertex shader.
     * @param fragmentShaderPath The path to the fragment shader.
     * @return The OpenGL ID for the shader program.
     */
    GLuint createShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    /**
     * @brief Compiles a vertex or fragment shader from its source code.
     *
     * @param shaderContent The shader source code.
     * @param type The shader type (vertex or fragment).
     * @return The OpenGL ID for the compiled shader.
     */
    GLuint compile(const std::string &shaderContent, GLenum type);

    /**
     * @brief Reads the content of a file specified by its path.
     *
     * @param path The file path to read.
     * @return The content of the file as a string.
     */
    std::string readStringFromFile(const std::string &path);
};

#endif
