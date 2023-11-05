#include "glm/gtc/matrix_transform.hpp"
#include "Model.hpp"
#include "engine/utils/Log.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/loader/ModelLoader.hpp"

Model::Model() = default;

void Model::loadFromFile(const std::string &path) {
    ModelData* modelData = ModelLoader::loadModel(path);
    if(modelData == nullptr) {
        TK_LOG_F("Engine") << "ModelData is empty.";
    }
    for (const auto &meshData: modelData->meshes) {
        std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(meshData->vertices,meshData->indices);
        std::shared_ptr<Material> material = std::make_shared<Material>();
        material->diffuse = meshData->material.diffuse;
        material->emissive = meshData->material.emissive;
        material->specular = meshData->material.specular;
        material->shininess = meshData->material.shininess;
        material->hasTexture = meshData->material.hasTexture;
        material->diffuseMap = meshData->material.diffuseMapId;
        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
        mesh->create(vertexBuffer,material);
        m_meshes.push_back(mesh);
    }
    TK_LOG("Engine") << "Successfully created the model";
}

const std::vector<std::shared_ptr<Mesh>> &Model::getMeshes() const {
    return m_meshes;
}

