#include <glad/glad.h>
#include "RenderWindow.hpp"
#include "Model.hpp"
#include "engine/utils/Log.hpp"
#include "ModelObject.hpp"

RenderWindow::RenderWindow(int width, int height) {
    initWindow(width, height);
    initOpenGL();
    initCamera();
    m_shader = std::make_shared<Shader>("engine/shaders/basic/basic_shader.vert", "engine/shaders/basic/basic_shader.frag");
    resize(width,height);
    m_renderQueue.reserve(1000);
    m_lightPos = glm::vec3(-1);
    setLightColor(glm::vec3(1));
}
RenderWindow::~RenderWindow() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
void RenderWindow::draw(ModelObject &modelObject) {
    m_camera->update();
    m_renderQueue.push_back(&modelObject);
}
void RenderWindow::display() {
//    glm::vec4 lightDirection = glm::transpose(glm::inverse(m_camera->getView())) * glm::vec4(m_lightPos,1.0f);
//    m_shader->bind();
//    m_shader->setUniformVec3("u_lightDirection",lightDirection);
//    for (const auto &model : m_renderQueue) {
//        glm::mat4 modelView = m_camera->getView() * model->getMatrices()[0];
//        glm::mat4 invModelView = glm::transpose(glm::inverse(modelView));
//
//        // Set vertex shader uniforms
//        m_shader->setUniformMatrix4fv("u_modelViewProj", m_camera->getViewProj() * model->getMatrices()[0]);
//        m_shader->setUniformMatrix4fv("u_modelView", modelView);
//        m_shader->setUniformMatrix4fv("u_invModelView", invModelView);
//        model->draw(m_shader);
//    }
//    m_shader->unbind();
//    m_renderQueue.clear();
    m_shader->bind();
    std::map<Mesh*,std::vector<glm::mat4>> matrices;
    for (const auto &modelObject : m_renderQueue) {
        const Model* model = modelObject->getModel();
        if(!model) continue;
        for (int i = 0;i<model->getMeshes().size();++i) {
            if(m_uniformBuffers.find(model->getMeshes()[i].get()) == m_uniformBuffers.end()) {
                UniformBuffer buffer{};
                buffer.createBuffer();
                m_uniformBuffers[model->getMeshes()[i].get()] = buffer;
            }
            if(matrices.find(model->getMeshes()[i].get()) == matrices.end()) {
                matrices[model->getMeshes()[i].get()] = std::vector<glm::mat4>();
            }
            matrices[model->getMeshes()[i].get()].push_back(modelObject->getMatrices()[i]);
        }
    }
    glm::vec4 lightDirection = glm::transpose(glm::inverse(m_camera->getView())) * glm::vec4(m_lightPos,1.0f);
    m_shader->setUniformVec3("u_lightDirection",lightDirection);
    m_shader->setUniformMatrix4fv("u_CameraViewProj",m_camera->getViewProj());
    for (auto &pair: m_uniformBuffers) {
        pair.second.updateData(matrices[pair.first]);
        pair.second.bind();
        pair.first->draw(m_shader,matrices[pair.first].size());
    }
    m_shader->unbind();
    m_renderQueue.clear();
    glfwSwapBuffers(m_window);
}


void RenderWindow::initWindow(int width, int height) {
    glfwWindowHint(GLFW_FLOATING,GLFW_TRUE);
    m_window = glfwCreateWindow(width, height, "Tunks", nullptr, nullptr);
    if (m_window == nullptr) {
        TK_LOG_F("Engine") << "Window creation failed";
    }
}

void RenderWindow::initOpenGL() {
    glfwMakeContextCurrent(m_window);
    if (!gladLoadGL()) {
        TK_LOG_F("Engine")  << "GLAD initialization failed";
    }
    TK_LOG("Engine")  << "Running with OpenGL version: " << glGetString(GL_VERSION);
    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(0);
}

void RenderWindow::initCamera() {
    m_camera = std::make_shared<Camera>(90.0f,16/9);
    m_camera->translate(glm::vec3(0.0f, 0.0f, 0.0f));
    m_camera->update();
}

void RenderWindow::resize(int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
}

GLFWwindow *RenderWindow::getWindow() const {
    return m_window;
}

const std::shared_ptr<Camera> &RenderWindow::getCamera() const {
    return m_camera;
}

void RenderWindow::setLightPosition(glm::vec3 position) {
    this->m_lightPos = position;
}

void RenderWindow::setLightColor(glm::vec3 color) {
    m_shader->bind();
    m_shader->setUniformVec3("u_lightColor",glm::vec3(1.0f,1.f,1.0f));
    m_shader->unbind();
}

