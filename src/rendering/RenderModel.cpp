#include "RenderModel.hpp"
#include <GL/glew.h>
#include <array>

void RenderModel::createFromFile(const std::string &path) {
    std::array<Vertex, 4> vertices= {
            Vertex{-0.5f, -0.5f, 0.0f,
                        1.0f, 0.0f, 0.0f, 1.0f},
            Vertex{-0.5f, 0.5f, 0.0f,
                        0.0, 1.0f, 0.0f, 1.0f},
            Vertex{0.5f, -0.5f, 0.0f,
                        0.0f, 0.0f, 1.0f, 1.0f},
            Vertex{0.5f, 0.5f, 0.0f,
                   1.0f, 0.0f, 0.0f, 1.0f}

    };
    std::vector<uint32> indices = {
            0,1,2,
            0,2,3
    };
    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices.data(),vertices.size(),indices);

}
void RenderModel::draw() {
    m_vertexBuffer->bind();
    glDrawElements(GL_TRIANGLES,m_vertexBuffer->getNumIndices(),GL_UNSIGNED_INT, nullptr);
    m_vertexBuffer->unbind();
}
