
#include <iostream>
#include "VertexBuffer.hpp"
#include "Vertex.hpp"

VertexBuffer::VertexBuffer(std::vector<Vertex> vertices, std::vector<uint32> indices) {
    //create vao
    glGenVertexArrays(1, &m_vaoId);
    glBindVertexArray(m_vaoId);
    //create buffer
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    //add vertexBuffer attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, textureCoord));
    //create the index buffer
    m_numIndices = indices.size();
    glGenBuffers(1, &m_indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numIndices * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
    //unbind the current vao.
    unbind();
}


VertexBuffer::~VertexBuffer() {
    glDeleteVertexArrays(1, &m_vaoId);
    glDeleteBuffers(1, &m_bufferId);
    glDeleteBuffers(1, &m_indexBufferId);
}

void VertexBuffer::bind() const {
    glBindVertexArray(m_vaoId);
}

void VertexBuffer::unbind() const {
    glBindVertexArray(0);
}

uint32 VertexBuffer::getNumIndices() const {
    return m_numIndices;
}

