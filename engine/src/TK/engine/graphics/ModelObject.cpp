#include "ModelObject.hpp"
#include <glm/gtc/matrix_transform.hpp>

ModelObject::ModelObject() : ModelObject(nullptr) {}
ModelObject::ModelObject(Model *model) : m_model(model) {
    if(model!= nullptr)
        m_matrices.resize(model->getMeshes().size(),glm::mat4(1.0f));
}
void ModelObject::draw(std::shared_ptr<Shader> shader) {
    m_model->draw(shader);
}

void ModelObject::translate(glm::vec3 move) {
    for (auto &matrix: m_matrices) {
        matrix = glm::translate(matrix,move);
    }
}

void ModelObject::rotate(float degrees, glm::vec3 axis) {
    for (auto &matrix: m_matrices) {
        matrix = glm::rotate(matrix, degrees, axis);
    }
}

void ModelObject::setModel(Model *model) {
    m_model = model;
}


Model *ModelObject::getModel() const {
    return m_model;
}

const std::vector<glm::mat4> &ModelObject::getMatrices() const {
    return m_matrices;
}


