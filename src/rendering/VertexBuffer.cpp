//
// Created by kido on 10/31/23.
//

#include <iostream>
#include "VertexBuffer.hpp"
#include "Vertex.hpp"

VertexBuffer::VertexBuffer(void *data, uint32 numVertices) {
    //create vao
    glGenVertexArrays(1,&m_vaoId);
    glBindVertexArray(m_vaoId);

    //create buffer
    glGenBuffers(1,&m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER,m_bufferId);
    glBufferData(GL_ARRAY_BUFFER,numVertices * sizeof(Vertex),data,GL_STATIC_DRAW);

    //add vertexBuffer attributes
    glEnableVertexAttribArray(0);
    // 0: Attribute location, 3 components of type GL_FLOAT, not normalized, stride is sizeof(Vertex), data starts at offsetof(Vertex, x).
    glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, x));
    //unbind the current vao.
    unbind();
}


VertexBuffer::~VertexBuffer() {
    glDeleteVertexArrays(1,&m_bufferId);
    glDeleteBuffers(1,&m_bufferId);
}

void VertexBuffer::bind() const {
    glBindVertexArray(m_vaoId);
}

void VertexBuffer::unbind() const {
    glBindVertexArray(0);
}
