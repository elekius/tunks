#ifndef TUNKS_VERTEXBUFFER_HPP
#define TUNKS_VERTEXBUFFER_HPP

#include "../Defines.hpp"
#include "Vertex.hpp"
#include <GL/glew.h>
#include <vector>

/**
 * A simple vertexBuffer class. That uses VAO for storing the vertices buffer and the indices buffer.
 * It can simple be binded with the the provided methods.
 * @author ChikyuKido
 */
class VertexBuffer {
public:
    /**
     * Creates a new vertex and index buffer in a vao.
     * @param vertices the vertices
     * @param indices the indices
     */
    VertexBuffer(std::vector<Vertex> vertices, std::vector<uint32> indices);

    virtual ~VertexBuffer();
    /**
     * Bind the vao
     */
    void bind() const;
    /**
     * unbind the vao
     */
    void unbind() const;
    /**
     * Returns the number of the indices.
     * Mainly used for the glDrawElements
     * @see glDrawElements
     * @return the number of the indices
     */
    uint32 getNumIndices() const;

private:
    GLuint m_bufferId;
    GLuint m_vaoId;
    uint32 m_indexBufferId;
    uint32 m_numIndices;
};


#endif
