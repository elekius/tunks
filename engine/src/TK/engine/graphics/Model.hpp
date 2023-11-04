#ifndef TUNKS_MODEL_HPP
#define TUNKS_MODEL_HPP

#include "glm/glm.hpp"
#include <vector>
#include "Mesh.hpp"

/**
 * The imported rendermodel. It consists of meshes.
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
    /**
     * Draws all the meshes
     * @param shader the basic shader so the meshes can apply their material to the basic shader when drawing
     */
    void draw(const std::shared_ptr<Shader>& shader);


private:
    std::vector<std::shared_ptr<Mesh>> m_meshes;
};

#endif
