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
 * A simple material struct
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
 * The mesh class for the RenderModel. It containes the material and the vertexBuffer of the mesh.
 * @author ChikyuKido
 */
class Mesh {
public:
    /**
     * Creates a new Mesh
     */
    Mesh();

    virtual ~Mesh();

    /**
     * Creates a mesh with the given material and vertexBuffer.
     * @param path
     */
    void create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<Material> material);

    /**
     * Binds the VertexBuffer and then draw the vertices with a indexBuffer. Also unbinds the buffer afterwards
     * Sets the uniforms for the fragment shader also the material settings
     * @param shader The basic shader
     */
    void draw(const std::shared_ptr<Shader>& shader);

private:
    std::shared_ptr<Material> m_material;
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
};


#endif
