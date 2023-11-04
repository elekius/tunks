#ifndef TUNKS_MODELOBJECT_HPP
#define TUNKS_MODELOBJECT_HPP

#include <glm/glm.hpp>
#include "Model.hpp"

/**
 * A simple wrapper for the Model. It contains a reference to the actual model and just stores a own matrix.
 * This matrix then gets applied before the draw and so you can have multiple objects with only one model.
 * @see Model.hpp
 * @author ChikyuKido
 */
class ModelObject {
public:
    ModelObject();
    ModelObject(Model* model);
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
     * Draws the model to the screen.
     * @param shader
     */
    void draw(std::shared_ptr<Shader> shader);

    void setModel(Model *model);
    [[nodiscard]] const std::vector<glm::mat4> &getMatrices() const;

    [[nodiscard]] Model *getModel() const;

private:
    Model* m_model;
    std::vector<glm::mat4> m_matrices;
};


#endif
