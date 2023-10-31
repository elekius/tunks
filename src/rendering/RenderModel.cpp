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
    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices.data(),vertices.size());

}
void RenderModel::draw() {
    m_vertexBuffer->bind();
    glDrawArrays(GL_TRIANGLES,0,m_numVertices);
    m_vertexBuffer->unbind();
}
