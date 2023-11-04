

#ifndef TUNKS_MODELDATA_HPP
#define TUNKS_MODELDATA_HPP
#include <glad/glad.h>
#include <vector>
#include <memory>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "TK/engine/Defines.hpp"
#include "TK/engine/graphics/Vertex.hpp"

/**
 * The whole data of a model which is loaded by a .TK file
 * @see ModelLoader.hpp
 * @author ChikyuKido
 */

struct MaterialData {
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emissive;
    float shininess;
    GLuint diffuseMapId;
    bool hasTexture = false;

    MaterialData() = default;

};
struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<uint32> indices;
    MaterialData material;
};
struct ModelData {
    std::vector<MaterialData> materials;
    std::vector<std::shared_ptr<MeshData>> meshes;
};

#endif
