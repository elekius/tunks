#include <iostream>
#include "ShaderStorageBuffer.hpp"

void ShaderStorageBuffer::createBuffer() {
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bufferId);
    //TODO: Maybe not fixed size 1000
    glBufferData(GL_SHADER_STORAGE_BUFFER, 1000 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,m_bufferId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
void ShaderStorageBuffer::bind() const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,m_bufferId);
}
void ShaderStorageBuffer::updateData(const std::vector<glm::mat4>& matrices) const {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bufferId);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, matrices.size() * sizeof(glm::mat4), matrices.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

ShaderStorageBuffer::~ShaderStorageBuffer() {
    glDeleteBuffers(1, &m_bufferId);
}

void ShaderStorageBuffer::unbind() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);
}


