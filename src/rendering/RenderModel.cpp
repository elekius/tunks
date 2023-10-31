#include "RenderModel.hpp"
#include <GL/glew.h>
#include <array>

void RenderModel::createFromFile(const std::string &path) {
    std::array<Vertex, 3> vertices= {
            Vertex(-0.5f,-0.5f,0.0f),
            Vertex(0.0f,0.5f,0.0f),
            Vertex(0.5f,-0.5f,0.0f),
    };
    m_numVertices = vertices.size();
    glGenBuffers(1,&m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER,m_bufferId);
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(Vertex),vertices.data(),GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    // 0: Attribute location, 3 components of type GL_FLOAT, not normalized, stride is sizeof(Vertex), data starts at offsetof(Vertex, x).
    glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, x));
    //unbinding
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderModel::draw() {
    glBindBuffer(GL_ARRAY_BUFFER,m_bufferId);
    glDrawArrays(GL_TRIANGLES,0,m_numVertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
