#ifndef TUNKS_RENDERMODEL_HPP
#define TUNKS_RENDERMODEL_HPP


#include <string>
#include <vector>
#include <GL/glew.h>
#include <memory>
#include "Vertex.hpp"
#include "VertexBuffer.hpp"

class RenderModel {
public:
    void createFromFile(const std::string &path);
    void draw();
private:
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
    int m_numVertices;
};


#endif
