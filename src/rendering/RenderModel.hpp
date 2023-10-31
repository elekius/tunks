#ifndef TUNKS_RENDERMODEL_HPP
#define TUNKS_RENDERMODEL_HPP


#include <string>
#include <vector>
#include <GL/glew.h>
#include "Vertex.hpp"

class RenderModel {
public:
    void createFromFile(const std::string &path);
    void draw();
private:
    GLuint m_bufferId;
    int m_numVertices;
};


#endif
