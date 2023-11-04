#ifndef TUNKS_MODELLOADER_HPP
#define TUNKS_MODELLOADER_HPP

#include <string>
#include "ModelData.hpp"

/**
 * @author ChikyuKido
 */
class ModelLoader {
public:
    static ModelData* loadModel(std::string path);
};


#endif
