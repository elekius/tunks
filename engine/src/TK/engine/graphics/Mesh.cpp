
#include <iostream>
#include "Mesh.hpp"
#include "Shader.hpp"

void Mesh::draw(const std::shared_ptr<Shader>& shader,int instances) {
    std::cout << instances << std::endl;
    m_vertexBuffer->bind();
    //fragment shader uniforms
    shader->setUniformVec3("u_specular",m_material->specular);
    shader->setUniformVec3("u_emissive",m_material->emissive);
    shader->setUniformFloat("u_shininess",m_material->shininess);
    shader->setUniformBool("u_has_texture",m_material->hasTexture);
    if(m_material->hasTexture) {
        glBindTexture(GL_TEXTURE_2D, m_material->diffuseMap);
        shader->setUniformInt("u_diffuse_map", 0);
    }else {
        shader->setUniformVec3("u_diffuse",m_material->diffuse);
    }
    glDrawElementsInstanced(GL_TRIANGLES, m_vertexBuffer->getNumIndices(), GL_UNSIGNED_INT, nullptr,instances);
}


void Mesh::create(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<Material> material) {
    m_vertexBuffer = vertexBuffer;
    m_material = material;
}

Mesh::Mesh() {}

Mesh::~Mesh() {

}
