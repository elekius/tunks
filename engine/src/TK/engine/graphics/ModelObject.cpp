#include "ModelObject.hpp"
#include <glm/gtc/matrix_transform.hpp>

ModelObject::ModelObject() : ModelObject(nullptr) {}
ModelObject::ModelObject(Model *model) : m_model(model),m_matrix(1.0f) {

}


void ModelObject::draw(std::shared_ptr<Shader> shader) {
    m_model->draw(shader);
}

void ModelObject::translate(glm::vec3 move) {
    m_matrix = glm::translate(m_matrix, move);
}

void ModelObject::rotate(float degrees, glm::vec3 axis) {
    m_matrix = glm::rotate(m_matrix, degrees, axis);
}

void ModelObject::setModel(Model *model) {
    m_model = model;
}

const glm::mat4 &ModelObject::getMatrix() const {
    return m_matrix;
}

void ModelObject::setMatrix(const glm::mat4 &matrix) {
    m_matrix = matrix;
}
