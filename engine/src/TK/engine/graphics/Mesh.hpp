#ifndef TUNKS_MESH_HPP
#define TUNKS_MESH_HPP

#include <string>
#include <vector>
#include <memory>
#include "Vertex.hpp"
#include "VertexBuffer.hpp"
#include "glm/glm.hpp"
#include "Shader.hpp"


/**
 * @brief The material struct for a Mesh. It can also have a texture.
 *
 * This struct represents the material properties of a mesh, including diffuse color, specular color,
 * emissive color, shininess, and whether it has a texture. If it has a texture, the OpenGL texture ID is provided.
 * @author ChikyuKido
 */
struct Material {
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emissive;
    float shininess;
    bool hasTexture;
    GLuint diffuseMap;
};

/**
 * @brief This class represents a 3D mesh in the game. It manages the vertex buffer and the material.
 *
 * A Mesh is a fundamental component in 3D graphics, representing a 3D object's geometry and material properties.
 * It is composed of a VertexBuffer for vertex data and a Material for specifying how the mesh should be shaded.
 * @see VertexBuffer.hpp
 * @see Material
 * @author ChikyuKido
 */
class Mesh {
public:
    Mesh();
    virtual ~Mesh();

    /**
     * @brief Create a mesh with the given vertex buffer and material.
     *
     * @param vertexBuffer - A shared pointer to the VertexBuffer containing vertex data.
     * @param material - A shared pointer to the Material defining the material properties of the mesh.
     */
    void create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<Material> material);

    /**
     * @brief Draws the mesh with instanced rendering and sets various uniforms in the shader.
     *
     * The function performs instanced rendering and sets shader uniforms such as u_specular, u_emissive,
     * u_shininess, u_has_texture, u_diffuse_map (if hasTexture is true), and u_diffuse (if hasTexture is false).
     *
     * @param shader - A shared pointer to the Shader program to use for rendering.
     * @param instances - The number of instances to render (for instanced rendering).
     */
    void draw(const std::shared_ptr<Shader>& shader, int instances) const;

private:
    std::shared_ptr<Material> m_material;
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
};
#endif
