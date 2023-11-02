#include "Mesh.hpp"
#include "Shader.hpp"
#include <GL/glew.h>

void Mesh::draw(const std::shared_ptr<Shader>& shader) {
    m_vertexBuffer->bind();
    //fragment shader uniforms
    shader->setUniformVec3("u_diffuse",m_material->diffuse);
    shader->setUniformVec3("u_specular",m_material->specular);
    shader->setUniformVec3("u_emissive",m_material->emissive);
    shader->setUniformFloat("u_shininess",m_material->shininess);
    glDrawElements(GL_TRIANGLES, m_vertexBuffer->getNumIndices(), GL_UNSIGNED_INT, nullptr);
}


void Mesh::create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<Material> material) {
    m_vertexBuffer = vertexBuffer;
    m_material = material;
}

Mesh::Mesh() {}

Mesh::~Mesh() {}
