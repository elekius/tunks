

#ifndef TUNKS_MODELDATA_HPP
#define TUNKS_MODELDATA_HPP

#include <vector>
#include <memory>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "TK/engine/Defines.hpp"

/**
 * The whole data of a model which is loaded by a .TK file
 * @see ModelLoader.hpp
 * @author ChikyuKido
 */

struct Materiall {
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emissive;
    float shininess;
    std::string normalMap;
    bool hasTexture = false;
};
struct Meshh {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<uint32> indices;
    Materiall material;
};
struct ModelData {
    std::vector<Materiall> materials;
    std::vector<std::shared_ptr<Meshh>> meshes;
};

#endif
