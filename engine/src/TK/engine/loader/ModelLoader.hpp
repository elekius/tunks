#ifndef TUNKS_MODELLOADER_HPP
#define TUNKS_MODELLOADER_HPP

#include <string>
#include "ModelData.hpp"

/**
 * @author ChikyuKido
 */
class ModelLoader {
public:
    static ModelData* loadModel(const std::string& path);
    static GLuint loadTexture(const std::string& path);
};


#endif
