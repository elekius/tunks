#ifndef TUNKS_VERTEXBUFFER_HPP
#define TUNKS_VERTEXBUFFER_HPP

#include "Defines.hpp"
#include "Vertex.hpp"
#include <GL/glew.h>
#include <vector>

class VertexBuffer {
public:
    VertexBuffer(std::vector<Vertex> vertices,std::vector<uint32> indices);

    virtual ~VertexBuffer();

    void bind() const;
    void unbind() const;

    uint32 getNumIndices() const;

private:
    GLuint m_bufferId;
    GLuint m_vaoId;
    uint32 m_indexBufferId;
    uint32 m_numIndices;
};


#endif
