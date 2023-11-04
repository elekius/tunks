#include "ModelLoader.hpp"
#include "engine/utils/Log.hpp"
#include "glad/glad.h"
#include "stb_image.h"
#include <filesystem>
namespace fs = std::filesystem;

ModelData *ModelLoader::loadModel(const std::string& path) {
    TK_LOG("Engine") << "Try loading model file: " << path;
    std::ifstream in = std::ifstream(path, std::ios::in | std::ios::binary);
    if (!in.is_open()) {
        TK_LOG_F("Engine") << "Error reading model file: " << path;
    }
    auto* modelData = new ModelData();
    //reading in the materials
    uint32 numMaterials = 0;
    in.read((char*)&numMaterials, 4);
    TK_LOG("Engine") << "Model has " << numMaterials << " Materials";
    for (uint32 i = 0; i < numMaterials; ++i) {
        MaterialData material{};
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
        // maybe a bit overkill, but I don't want to do it with sub string
        fs::path tmpPath = path;
        fs::path parentDirectory = tmpPath.parent_path();
        material.diffuseMapId = loadTexture(parentDirectory.string() + "/"+ diffuseMapName);
        modelData->materials.push_back(material);
    }
    TK_LOG("Engine") << "Finished loading materials start loading meshes";
    uint32 numMeshes = 0;
    in.read((char*)&numMeshes,4);
    TK_LOG("Engine") << "Found " << numMeshes << " meshes";
    for (uint32 i = 0; i < numMeshes; ++i) {
        std::shared_ptr<MeshData> mesh = std::make_shared<MeshData>();
        uint32 materialIndex = 0;
        uint32 numVertices = 0;
        uint32 numIndices = 0;
        in.read((char*)&materialIndex,4);
        in.read((char*)&numVertices,4);
        in.read((char*)&numIndices,4);
        for (uint32 j = 0; j < numVertices; ++j) {
            Vertex vertex{};
            in.read((char*)&vertex.position,12);
            in.read((char*)&vertex.normal,12);
            in.read((char*)&vertex.textureCoord,8);
            mesh->vertices.push_back(vertex);
        }
        for (uint32 j = 0; j < numIndices; ++j) {
            uint32 index = 0;
            in.read((char*)&index,4);
            mesh->indices.push_back(index);
        }
        mesh->material = modelData->materials[materialIndex];
        modelData->meshes.push_back(mesh);
    }
    TK_LOG("Engine") << "Successfully load model";
    return modelData;
}

GLuint ModelLoader::loadTexture(const std::string &path) {
    TK_LOG("Engine") << "Loading texture: " << path;
    GLuint diffuseMapId = 0;
    int32 textureWidth = 0;
    int32 textureHeight = 0;
    int32 bitsPerPixel = 0;
    glGenTextures(1, &diffuseMapId);
    stbi_set_flip_vertically_on_load(true);
    {
        auto textureBuffer = stbi_load(path.c_str(), &textureWidth, &textureHeight, &bitsPerPixel, 4);
        assert(textureBuffer);

        glBindTexture(GL_TEXTURE_2D, diffuseMapId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
        if(textureBuffer) {
            stbi_image_free(textureBuffer);
        }
    }
    return diffuseMapId;
}
