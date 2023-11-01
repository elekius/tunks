#include "RenderModel.hpp"
#include "core/utils/Log.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <fstream>
#include <GL/glew.h>
#include <array>

void RenderModel::createFromFile(const std::string &path) {
    TK_LOG << "Try loading model file: " << path;
    uint32 numVertices = 0;
    uint32 numIndices = 0;
    std::ifstream input = std::ifstream(path, std::ios::in | std::ios::binary);
    if (!input.is_open()) {
        TK_LOG_E << "Error reading model file: " << path;
        return;
    }
    input.read((char *) &numVertices, sizeof(uint32));
    input.read((char *) &numIndices, sizeof(uint32));
    TK_LOG << "Successfully read info for model. Has " << numVertices << " vertices and " << numIndices << " indices";
    std::vector<Vertex> vertices;
    vertices.reserve(numVertices);
    std::vector<uint32> indices;
    indices.reserve(numIndices);
    for (uint32 i = 0; i < numVertices; ++i) {
        Vertex vertex{};
        input.read((char *) &vertex.x, sizeof(float));
        input.read((char *) &vertex.y, sizeof(float));
        input.read((char *) &vertex.z, sizeof(float));
        vertex.r = 1.0f;
        vertex.g = 1.0f;
        vertex.b = 1.0f;
        vertex.a = 1.0f;
        vertices.push_back(vertex);
    }
    for (uint32 i = 0; i < numVertices; ++i) {
        uint32 index;
        input.read((char *) &index, sizeof(uint32));
        indices.push_back(index);
    }
    m_vertexBuffer = std::make_unique<VertexBuffer>(vertices, indices);
    TK_LOG << "Successfully created the model";

}

void RenderModel::draw() {
    m_vertexBuffer->bind();
    glDrawElements(GL_TRIANGLES, m_vertexBuffer->getNumIndices(), GL_UNSIGNED_INT, nullptr);
    m_vertexBuffer->unbind();
}

const glm::mat4 &RenderModel::getMatrix() const {
    return m_matrix;
}

void RenderModel::translate(glm::vec3 move) {
    m_matrix = glm::translate(m_matrix, move);
}

void RenderModel::rotate(float degrees, glm::vec3 axis) {
    m_matrix = glm::rotate(m_matrix, degrees, axis);
}

RenderModel::RenderModel() : m_matrix(1.0f) {}
