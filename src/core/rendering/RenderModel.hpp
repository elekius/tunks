#ifndef TUNKS_RENDERMODEL_HPP
#define TUNKS_RENDERMODEL_HPP

#include <glm/glm.hpp>
#include <vector>
#include "Mesh.hpp"

/**
 *
 * @author ChikyuKido
 */
class RenderModel {
public:
    RenderModel();
    void loadFromFile(const std::string& path);
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

    void draw(const std::shared_ptr<Shader>& shader);

    /**
     * Gets the model matrix.
     * @return the matrix of the model
     */
    [[nodiscard]] const glm::mat4 &getMatrix() const;
private:
    glm::mat4 m_matrix;
    std::vector<std::shared_ptr<Mesh>> m_meshes;
    void createMesh(std::ifstream &inputStream);
};


#endif
