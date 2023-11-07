#ifndef TUNKS_MODELOBJECT_HPP
#define TUNKS_MODELOBJECT_HPP

#include <glm/glm.hpp>
#include "Model.hpp"
/**
 * @brief A simple wrapper for the Model. It contains a reference to the actual model
 * and stores its own vector of matrices.
 *
 * Each matrix in the vector corresponds to a mesh within the model, allowing
 * individual transformations for each mesh.
 * @see Model.hpp
 * @author ChikyuKido
 */
class ModelObject {
public:
    /**
     * @brief Default constructor for ModelObject.
     */
    ModelObject();

    /**
     * @brief Constructor for ModelObject with a specified model.
     *
     * @param model A shared pointer to the model associated with this ModelObject.
     */
    ModelObject(std::shared_ptr<Model> model);

    /**
     * @brief Moves the entire model with the given vector.
     *
     * @param move A 3D vector specifying the translation to apply to the model.
     */
    void translate(glm::vec3 move);

    /**
     * @brief Rotates the entire model by the given number of degrees around the specified axis.
     *
     * @param degrees The degrees to rotate.
     * @param axis The axis around which to rotate.
     */
    void rotate(float degrees, glm::vec3 axis);

    /**
     * @brief Sets the rotation of the entire model to the given degrees around the specified axis.
     *
     * @param degrees The degrees to set the rotation to.
     * @param axis The axis around which to set the rotation.
     */
    void setRotation(float degrees, glm::vec3 axis);

    /**
     * @brief Scales the entire model by the specified scaling factors.
     *
     * @param scale A 3D vector specifying the scaling factors.
     */
    void scale(glm::vec3 scale);

    /**
     * @brief Moves a specific mesh at the given index with the provided vector.
     *
     * @param move A 3D vector specifying the translation to apply to the mesh.
     * @param index The index of the mesh to move.
     */
    void translate(glm::vec3 move, int index);

    /**
     * @brief Rotates a specific mesh at the given index by the specified degrees around the provided axis.
     *
     * @param degrees The degrees to rotate.
     * @param axis The axis around which to rotate.
     * @param index The index of the mesh to rotate.
     */
    void rotate(float degrees, glm::vec3 axis, int index);

    /**
     * @brief Scales a specific mesh at the given index by the specified scaling factors.
     *
     * @param scale A 3D vector specifying the scaling factors.
     * @param index The index of the mesh to scale.
     */
    void scale(glm::vec3 scale, int index);

    [[nodiscard]] const std::vector<glm::mat4> &getMatrices() const;
    [[nodiscard]] const std::shared_ptr<Model> &getModel() const;

private:
    std::shared_ptr<Model> m_model;
    std::vector<glm::mat4> m_matrices;
};


#endif
