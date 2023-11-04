#include "ModelLoader.hpp"
#include "engine/utils/Log.hpp"

ModelData *ModelLoader::loadModel(std::string path) {
    TK_LOG << "Try loading model file: " << path;
    std::ifstream in = std::ifstream(path, std::ios::in | std::ios::binary);
    if (!in.is_open()) {
        TK_LOG_F << "Error reading model file: " << path;
    }
    auto* modelData = new ModelData();
    //reading in the materials
    uint32 numMaterials = 0;
    in.read((char*)&numMaterials, 4);
    for (uint32 i = 0; i < numMaterials; ++i) {
        Materiall material{};
        in.read((char*)&material.diffuse,12);
        in.read((char*)&material.specular,12);
        in.read((char*)&material.emissive,12);
        in.read((char*)&material.shininess,4);

        uint32 lengthDiffuseMapString = 0;
        in.read((char*)&lengthDiffuseMapString,4);
        std::string diffuseMapName(lengthDiffuseMapString, '\0');
        if(lengthDiffuseMapString != 0) {
            in.read((char*)&diffuseMapName[0],lengthDiffuseMapString);
            material.hasTexture = true;
        }else {
            diffuseMapName = "";
            material.hasTexture = false;
        }
        material.normalMap = diffuseMapName;
        modelData->materials.push_back(std::move(material));
    }

    uint32 numMeshes = 0;
    in.read((char*)&numMeshes,4);
    for (uint32 i = 0; i < numMeshes; ++i) {
        std::shared_ptr<Meshh> mesh = std::make_shared<Meshh>();
        uint32 materialIndex = 0;
        uint32 numVertices = 0;
        uint32 numIndices = 0;
        in.read((char*)&materialIndex,4);
        in.read((char*)&numVertices,4);
        in.read((char*)&numIndices,4);
        for (uint32 j = 0; j < numVertices; ++j) {
            glm::vec3 position{};
            glm::vec3 normal{};
            glm::vec2 texCoord{};
            in.read((char*)&position,12);
            in.read((char*)&normal,12);
            in.read((char*)&texCoord,8);
            mesh->positions.push_back(position);
            mesh->normals.push_back(normal);
            mesh->texCoords.push_back(texCoord);
        }
        for (uint32 j = 0; j < numIndices; ++j) {
            uint32 index = 0;
            in.read((char*)&index,4);
            mesh->indices.push_back(index);
        }
        mesh->material = modelData->materials[materialIndex];
    }
    return modelData;
}
