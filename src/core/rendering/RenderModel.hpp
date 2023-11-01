#ifndef TUNKS_RENDERMODEL_HPP
#define TUNKS_RENDERMODEL_HPP


#include <string>
#include <vector>
#include <GL/glew.h>
#include <memory>
#include "Vertex.hpp"
#include "VertexBuffer.hpp"
#include "glm/glm.hpp"

/**
 * A small wrapper for a 3d model. The model can be created with a tk file. The tk files needs to be converted with the TunksObjConverter
 * @author ChikyuKido
 */
class RenderModel {
public:
    /**
     * Creates a new RenderModel
     */
    RenderModel();
    /**
     * Loads the model from a .tk file and create the associated buffers.
     * @param path
     */
    void createFromFile(const std::string &path);

    /**
     * Binds the VertexBuffer and then draw the vertices with a indexBuffer. Also unbinds the buffer afterwards
     */
    void draw();

    /**
     * Moves the model with the given value
     * @param move the vec3 to move
     */
    void translate(glm::vec3 move);

    /**
     * Rotates the model in the given degrees in the given axis
     * @param degrees the degrees to rotate
     * @param axis the axis in which it should be rotated
     */
    void rotate(float degrees, glm::vec3 axis);

    /**
     * Gets the model matrix.
     * @return the matrix of the model
     */
    [[nodiscard]] const glm::mat4 &getMatrix() const;

private:
    glm::mat4 m_matrix;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
};


#endif
