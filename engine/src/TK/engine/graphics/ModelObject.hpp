#ifndef TUNKS_MODELOBJECT_HPP
#define TUNKS_MODELOBJECT_HPP

#include <glm/glm.hpp>
#include "Model.hpp"

/**
 * A simple wrapper for the Model. It contains a reference to the actual model and just stores a own vector of matrix.
 * Each matrix is for each mesh the model has. So you can transform each mesh like you want.
 * @see Model.hpp
 * @author ChikyuKido
 */
class ModelObject {
public:
    ModelObject();
    ModelObject(std::shared_ptr<Model> model);
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

    void setRotation(float degrees, glm::vec3 axis);

    /**
     * Scales the model.
     * @param scale a vec3 to scale the model
     */
    void scale(glm::vec3 scale);

    /**
     * Moves the mesh at the position index with the given value
     * @param move the vec3 to move
     */
    void translate(glm::vec3 move,int index);
    /**
     * Rotates the mesh at the position index in the given degrees in the given axis
     * @param degrees the degrees to rotate
     * @param axis the axis in which it should be rotated
     */
    void rotate(float degrees, glm::vec3 axis,int index);
    /**
     * Scales the mesh at the position index.
     * @param scale a vec3 to scale the model
     */
    void scale(glm::vec3 scale,int index);

    [[nodiscard]] const std::vector<glm::mat4> &getMatrices() const;
    [[nodiscard]] const std::shared_ptr<Model> &getModel() const;

private:
    std::shared_ptr<Model> m_model;
    std::vector<glm::mat4> m_matrices;
};


#endif
