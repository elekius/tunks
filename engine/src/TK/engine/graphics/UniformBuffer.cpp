#include <iostream>
#include "UniformBuffer.hpp"

void UniformBuffer::createBuffer() {
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_UNIFORM_BUFFER, m_bufferId);
    glBufferData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
void UniformBuffer::bind() {
    glBindBuffer(GL_UNIFORM_BUFFER,m_bufferId);
}
void UniformBuffer::unbind() {
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}
void UniformBuffer::updateData(const std::vector<glm::mat4>& matrices) {
    glBindBuffer(GL_UNIFORM_BUFFER, m_bufferId);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, matrices.size() * sizeof(glm::mat4), matrices.data());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


