#ifndef TUNKS_MODEL_HPP
#define TUNKS_MODEL_HPP

#include "glm/glm.hpp"
#include <vector>
#include "Mesh.hpp"

/**
 * @brief This class represents a 3D model consisting of meshes.
 *
 * A 3D model is composed of multiple meshes, each of which is a separate piece of the model.
 * @see Mesh.hpp
 * @author ChikyuKido
 */
class Model {
public:
    /**
     * @brief Default constructor for the Model class.
     */
    Model();

    /**
     * @brief Loads the meshes for the 3D model from a TK file.
     *
     * The TK file should be in the TK file format from the TunksObjConverter.
     *
     * @param path The path to the TK file.
     */
    void loadFromFile(const std::string& path);
    [[nodiscard]] const std::vector<std::shared_ptr<Mesh>> &getMeshes() const;

private:
    std::vector<std::shared_ptr<Mesh>> m_meshes; // Vector of shared pointers to the model's meshes.
};
#endif
