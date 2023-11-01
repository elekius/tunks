#ifndef TUNKS_MESH_HPP
#define TUNKS_MESH_HPP


#include <string>
#include <vector>
#include <GL/glew.h>
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
};

/**
 * A small wrapper for a 3d model. The model can be created with a tk file. The tk files needs to be converted with the TunksObjConverter
 * @author ChikyuKido
 */
class Mesh {
public:
    /**
     * Creates a new RenderModel
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
     */
    void draw(const std::shared_ptr<Shader>& shader);

private:
    std::shared_ptr<Material> m_material;
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
};


#endif
