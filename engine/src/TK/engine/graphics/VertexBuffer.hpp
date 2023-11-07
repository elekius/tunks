#ifndef TUNKS_VERTEXBUFFER_HPP
#define TUNKS_VERTEXBUFFER_HPP

#include <glad/glad.h>
#include <vector>
#include "TK/engine/Defines.hpp"
#include "Vertex.hpp"
/**
 * @brief A simple VertexBuffer class that uses a VAO to store vertex and index buffers.
 * It provides methods for binding and unbinding the VAO.
 *
 * This class is used for managing vertex and index buffers within a VAO.
 * @author ChikyuKido
 */
class VertexBuffer {
public:
    /**
     * @brief Creates a new vertex and index buffer in a VAO.
     *
     * @param vertices A vector of vertices.
     * @param indices A vector of indices.
     */
    VertexBuffer(std::vector<Vertex> vertices, std::vector<uint32> indices);

    virtual ~VertexBuffer();

    /**
     * @brief Bind the VAO.
     *
     * Binds the VAO for use in subsequent operations.
     */
    void bind() const;

    /**
     * @brief Unbind the VAO.
     *
     * Unbinds the VAO.
     */
    void unbind() const;

    [[nodiscard]] uint32 getNumIndices() const;

private:
    GLuint m_bufferId;
    GLuint m_vaoId;
    uint32 m_indexBufferId;
    uint32 m_numIndices;
};

#endif
