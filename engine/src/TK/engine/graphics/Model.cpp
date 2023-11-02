#include "glm/gtc/matrix_transform.hpp"
#include "Model.hpp"
#include "engine/utils/Log.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model() = default;

void Model::loadFromFile(const std::string &path) {
    TK_LOG << "Try loading model file: " << path;
    std::ifstream input = std::ifstream(path, std::ios::in | std::ios::binary);
    if (!input.is_open()) {
        TK_LOG_E << "Error reading model file: " << path;
        return;

    }

    //materials
    uint32 numMaterials = 0;
    input.read((char*) &numMaterials,sizeof(uint32));
    for (uint32 i = 0; i < numMaterials; ++i) {
        auto material = std::make_shared<Material>();
        input.read((char*)material.get(),sizeof(TKMaterial));

        uint32 diffuseMapNameLength = 0;
        input.read((char*)&diffuseMapNameLength, sizeof(uint32));
        std::string diffuseMapName(diffuseMapNameLength, '\0');
        input.read((char*)&diffuseMapName[0], diffuseMapNameLength);

        uint32 normalMapNameLength = 0;
        input.read((char*)&normalMapNameLength, sizeof(uint32));
        std::string normalMapName(normalMapNameLength, '\0');
        input.read((char*)&normalMapName[0], normalMapNameLength);

        assert(diffuseMapNameLength > 0);
        assert(normalMapNameLength > 0);

        int32 textureWidth = 0;
        int32 textureHeight = 0;
        int32 bitsPerPixel = 0;
        glGenTextures(2, &material->diffuseMap);
        stbi_set_flip_vertically_on_load(true);
        {
            auto textureBuffer = stbi_load(diffuseMapName.c_str(), &textureWidth, &textureHeight, &bitsPerPixel, 4);

            assert(textureBuffer);
            assert(material->diffuseMap);

            glBindTexture(GL_TEXTURE_2D, material->diffuseMap);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);

            if(textureBuffer) {
                stbi_image_free(textureBuffer);
            }
        }

        {
            auto textureBuffer = stbi_load(normalMapName.c_str(), &textureWidth, &textureHeight, &bitsPerPixel, 4);
            assert(textureBuffer);
            assert(material->normalMap);

            glBindTexture(GL_TEXTURE_2D, material->normalMap);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);

            if(textureBuffer) {
                stbi_image_free(textureBuffer);
            }
        }
        glBindTexture(GL_TEXTURE_2D,0);
        m_materials.push_back(material);
    }

    //mesh
    uint32 numMeshes = 0;
    input.read((char *) &numMeshes, sizeof(uint32));
    m_meshes.reserve(numMeshes);
    for (int i = 0; i < numMeshes; ++i) {
        createMesh(input);
    }

    TK_LOG << "Successfully created the model";
}

void Model::createMesh(std::ifstream &inputStream) {
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<Material> material = std::make_shared<Material>();
    uint32 materialIndex = 0;
    inputStream.read((char *)&materialIndex, sizeof(uint32));
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

        inputStream.read((char *) &vertex.textureCoord.x, sizeof(float));
        inputStream.read((char *) &vertex.textureCoord.y, sizeof(float));

        vertices.push_back(vertex);
    }
    for (uint32 i = 0; i < numVertices; ++i) {
        uint32 index;
        inputStream.read((char *) &index, sizeof(uint32));
        indices.push_back(index);
    }
    vertexBuffer = std::make_shared<VertexBuffer>(vertices, indices);
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    mesh->create(vertexBuffer,m_materials[materialIndex]);
    m_meshes.push_back(mesh);
}


void Model::draw(const std::shared_ptr<Shader>& shader) {
    for (auto &mesh: m_meshes) {
        mesh->draw(shader);
    }
}

