#ifndef TUNKS_MODEL_HPP
#define TUNKS_MODEL_HPP

#include "glm/glm.hpp"
#include <vector>
#include "Mesh.hpp"

/**
 * This class representing the 3D model which consists of meshes.
 * @author ChikyuKido
 */
class Model {
public:
    Model();
    /**
     * Creates the meshes for the renderModel. The file should be in the TK file format from the TunksObjConverter
     * @param path the path to the tk file
     */
    void loadFromFile(const std::string& path);
    [[nodiscard]] const std::vector<std::shared_ptr<Mesh>> &getMeshes() const;

private:
    std::vector<std::shared_ptr<Mesh>> m_meshes;
};
#endif
