#include <glm/gtc/matrix_transform.hpp>
#include "RenderModel.hpp"
#include "core/utils/Log.hpp"

RenderModel::RenderModel() : m_matrix(1.0f) {}

void RenderModel::loadFromFile(const std::string &path) {
    TK_LOG << "Try loading model file: " << path;
    std::ifstream input = std::ifstream(path, std::ios::in | std::ios::binary);
    if (!input.is_open()) {
        TK_LOG_E << "Error reading model file: " << path;
        return;
    }
    uint32 numMeshes = 0;
    input.read((char *) &numMeshes, sizeof(uint32));
    m_meshes.reserve(numMeshes);
    for (int i = 0; i < numMeshes; ++i) {
        createMesh(input);
    }

    TK_LOG << "Successfully created the model";
}

void RenderModel::createMesh(std::ifstream &inputStream) {
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<Material> material = std::make_shared<Material>();

    inputStream.read((char *) material.get(), sizeof(Material));
    uint32 numVertices = 0;
    uint32 numIndices = 0;
    inputStream.read((char *) &numVertices, sizeof(uint32));
    inputStream.read((char *) &numIndices, sizeof(uint32));
    TK_LOG << "Successfully read info for model. Has " << numVertices << " vertices and " << numIndices << " indices";
    std::vector<Vertex> vertices;
    vertices.reserve(numVertices);
    std::vector<uint32> indices;
    indices.reserve(numIndices);
    for (uint32 i = 0; i < numVertices; ++i) {
        Vertex vertex{};
        inputStream.read((char *) &vertex.position.x, sizeof(float));
        inputStream.read((char *) &vertex.position.y, sizeof(float));
        inputStream.read((char *) &vertex.position.z, sizeof(float));

        inputStream.read((char *) &vertex.normal.x, sizeof(float));
        inputStream.read((char *) &vertex.normal.y, sizeof(float));
        inputStream.read((char *) &vertex.normal.z, sizeof(float));

        vertices.push_back(vertex);
    }
    for (uint32 i = 0; i < numVertices; ++i) {
        uint32 index;
        inputStream.read((char *) &index, sizeof(uint32));
        indices.push_back(index);
    }
    vertexBuffer = std::make_shared<VertexBuffer>(vertices, indices);
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    mesh->create(vertexBuffer,material);
    m_meshes.push_back(mesh);
}


void RenderModel::translate(glm::vec3 move) {
    m_matrix = glm::translate(m_matrix, move);
}

void RenderModel::rotate(float degrees, glm::vec3 axis) {
    m_matrix = glm::rotate(m_matrix, degrees, axis);
}

void RenderModel::draw(const std::shared_ptr<Shader>& shader) {
    for (auto &mesh: m_meshes) {
        mesh->draw(shader);
    }
}

const glm::mat4 &RenderModel::getMatrix() const {
    return m_matrix;
}

