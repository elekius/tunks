#ifndef TUNKS_RENDERMODEL_HPP
#define TUNKS_RENDERMODEL_HPP


#include <string>
#include <vector>
#include <GL/glew.h>
#include <memory>
#include "Vertex.hpp"
#include "VertexBuffer.hpp"
#include "glm/glm.hpp"

class RenderModel {
public:
    RenderModel();

    void createFromFile(const std::string &path);
    void draw();
    void translate(glm::vec3 move);
    void rotate(float amount, glm::vec3 axis);
    [[nodiscard]] const glm::mat4 &getMatrix() const;

private:
    glm::mat4 m_matrix;
    std::unique_ptr<VertexBuffer> m_vertexBuffer;
};


#endif
