#ifndef TUNKS_SHADERSTORAGEBUFFER_HPP
#define TUNKS_SHADERSTORAGEBUFFER_HPP


#include <vector>
#include <glad/glad.h>
#include "glm/glm.hpp"
/**
 * ShaderStorageBuffer class for managing shader storage buffer objects.
 * This class provides functionality to create, bind, and update data in a shader storage buffer.
 * @author ChikyuKido
 */
class ShaderStorageBuffer {
public:
    /**
     * @brief Unbind the shader storage buffer.
     *
     * This static function unbinds the currently bound shader storage buffer.
     */
    static void unbind();
    virtual ~ShaderStorageBuffer();

    /**
     * @brief Create a shader storage buffer.
     *
     * This function creates a shader storage buffer object.
     */
    void createBuffer();

    /**
     * @brief Bind the shader storage buffer.
     *
     * Binds the shader storage buffer for use in subsequent operations.
     */
    void bind() const;

    /**
     * @brief Update the data in the shader storage buffer.
     *
     * Updates the data in the shader storage buffer with the provided matrices.
     *
     * @param matrices A vector of glm::mat4 matrices to update the shader storage buffer with.
     */
    void updateData(const std::vector<glm::mat4> &matrices) const;

private:
    GLuint m_bufferId;

};

#endif
