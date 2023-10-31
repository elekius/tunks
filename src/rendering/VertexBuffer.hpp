#ifndef TUNKS_VERTEXBUFFER_HPP
#define TUNKS_VERTEXBUFFER_HPP

#include "Defines.hpp"
#include <GL/glew.h>

class VertexBuffer {
public:
    VertexBuffer(void* data,uint32 numVertices);

    virtual ~VertexBuffer();

    void bind() const;
    void unbind() const;

private:
    GLuint m_bufferId;
    GLuint m_vaoId;

};


#endif
