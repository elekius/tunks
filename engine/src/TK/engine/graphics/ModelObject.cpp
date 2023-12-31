#include "ModelObject.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

ModelObject::ModelObject() : ModelObject(nullptr) {}
ModelObject::ModelObject(std::shared_ptr<Model> model) : m_model(model){
    if(model!= nullptr)
        m_matrices.resize(model->getMeshes().size(),glm::mat4(1.0f));
}

void ModelObject::translate(glm::vec3 move) {
    for (auto &matrix: m_matrices) {
        matrix = glm::translate(matrix,move);
    }
}

void ModelObject::rotate(float degrees, glm::vec3 axis) {
    for (auto &matrix: m_matrices) {
        matrix = glm::rotate(matrix, glm::radians(degrees), axis);
    }
}

void ModelObject::scale(glm::vec3 scale) {
    for (auto &matrix: m_matrices) {
        matrix = glm::scale(matrix,scale);
    }
}

void ModelObject::rotate(float degrees, glm::vec3 axis, int index) {
    m_matrices[index]  = glm::rotate(m_matrices[index],glm::radians(degrees), axis);
}

void ModelObject::translate(glm::vec3 move, int index) {
    m_matrices[index]  = glm::translate(m_matrices[index],move);
}

void ModelObject::scale(glm::vec3 scale, int index) {
    m_matrices[index]  = glm::scale(m_matrices[index],scale);
}


const std::vector<glm::mat4> &ModelObject::getMatrices() const {
    return m_matrices;
}
void resetRotation(glm::mat4 &matrix){
    glm::vec3 translation, skew;
    glm::vec4 perspective;
    glm::quat rotation;
    glm::vec3 scale;
    glm::decompose(matrix, scale, rotation, translation, skew, perspective);

    matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, translation);
    matrix = glm::scale(matrix, scale);
}
void ModelObject::setRotation(float degrees, glm::vec3 axis) {
    for (auto &matrix: m_matrices) {
        resetRotation(matrix);
        matrix = glm::rotate(matrix, glm::radians(degrees), axis);
    }
}

const std::shared_ptr<Model> &ModelObject::getModel() const {
    return m_model;
}





