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
 * The material struct for a Mesh. It can also have a texture
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
 * This class representing a 3D mesh in the game. It manages the vertex buffer and the material.
 * @author ChikyuKido
 */
class Mesh {
public:

    //default constructor for the Mesh
    Mesh();
    virtual ~Mesh();

    /**
     * Create a mesh with the given vertex buffer and material.
     *
     * @param vertexBuffer - A shared pointer to the VertexBuffer containing vertex data.
     * @param material - A shared pointer to the Material defining the material properties of the mesh.
     */
    void create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<Material> material);


    /**
     * Draws the mesh with instanced rendering and sets the following uniforms:
     * u_specular, u_emissive, u_shininess, u_has_texture, u_diffuse_map (if hasTexture is true), u_diffuse (if hasTexture is false):
     * @param shader - A shared pointer to the Shader program to use for rendering.
     * @param instances - The number of instances to render (for instanced rendering).
     */
    void draw(const std::shared_ptr<Shader>& shader,int instances);

private:
    std::shared_ptr<Material> m_material;
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
};
#endif
