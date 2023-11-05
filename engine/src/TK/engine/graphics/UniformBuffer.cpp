#include <iostream>
#include "UniformBuffer.hpp"

void UniformBuffer::createBuffer() {
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bufferId);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 40000 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,m_bufferId);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
void UniformBuffer::bind() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,m_bufferId);
}
void UniformBuffer::unbind() {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);
}
void UniformBuffer::updateData(const std::vector<glm::mat4>& matrices) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_bufferId);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, matrices.size() * sizeof(glm::mat4), matrices.data());
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

UniformBuffer::~UniformBuffer() {
    glDeleteBuffers(1, &m_bufferId);
}


