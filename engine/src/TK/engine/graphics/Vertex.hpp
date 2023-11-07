#ifndef TUNKS_VERTEX_HPP
#define TUNKS_VERTEX_HPP

#include "glm/glm.hpp"

/**
 * @brief Represents a 3D vertex with position, normal, and texture coordinates.
 *
 * This struct is used to define the properties of a 3D vertex, including its position
 * in 3D space, normal vector for shading, and texture coordinates for mapping textures.
 * @author ChikyuKido
 */
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoord;
};

#endif
