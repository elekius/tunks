#include "Shader.hpp"
#include "core/utils/Log.hpp"

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShader) {
    TK_LOG << "Create shader program for vertex: " << vertexShaderPath << " and: " << fragmentShader;
    m_shaderId = createShader(vertexShaderPath, fragmentShader);
    if (m_shaderId == 0) {
        TK_LOG_E << "Failed to create shader program.";
    } else {
        TK_LOG << "Successfully created shader with id: " << m_shaderId;
    }
}

Shader::~Shader() {
    glDeleteProgram(m_shaderId);
}

GLuint Shader::createShader(const std::string &vertexShaderPath, const std::string &fragmentShader) {
    std::string vertexShaderSource = readStringFromFile(vertexShaderPath);
    std::string fragmentShaderSource = readStringFromFile(fragmentShader);

    GLuint program = glCreateProgram();
    if (program == 0) {
        TK_LOG_E << "Failed to create shader program.";
        return 0;
    }
    GLuint vertexShaderId = compile(vertexShaderSource, GL_VERTEX_SHADER);
    if (vertexShaderId == 0) {
        TK_LOG_E << "Failed to compile the vertex shader.";
        glDeleteProgram(program);
        return 0;
    }

    GLuint fragmentShaderId = compile(fragmentShaderSource, GL_FRAGMENT_SHADER);
    if (fragmentShaderId == 0) {
        TK_LOG_E << "Failed to compile the fragment shader.";
        glDeleteShader(vertexShaderId);
        glDeleteProgram(program);
        return 0;
    }

    glAttachShader(program, vertexShaderId);
    glAttachShader(program, fragmentShaderId);
    glLinkProgram(program);

    return program;
}


GLuint Shader::compile(const std::string &shaderContent, GLenum type) {
    GLuint id = glCreateShader(type);
    const char *src = shaderContent.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        int length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        TK_LOG_E << "Shader compilation error: " << message;
        delete[] message;
        return 0;
    }

    return id;
}


void Shader::bind() {
    glUseProgram(m_shaderId);
}

void Shader::unbind() {
    glUseProgram(0);
}

std::string Shader::readStringFromFile(const std::string &path) {
    std::string shaderContent;
    std::ifstream fileStream(path);

    if (!fileStream.is_open()) {
        TK_LOG_E << "Failed to open file: " << path;
        return "";
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    shaderContent = buffer.str();

    if (shaderContent.empty()) {
        TK_LOG_W << "Shader file is empty: " << path;
    } else {
        TK_LOG << "Successfully read shader content from file: " << path;
    }

    fileStream.close();

    return shaderContent;
}

GLuint Shader::getShaderId() const {
    return m_shaderId;
}

void Shader::setUniformMatrix4fv(const std::string &name, const glm::mat4 &value) {
    GLint location = glGetUniformLocation(m_shaderId, name.c_str());
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    } else {
        TK_LOG_W << "Uniform not found: " << name;
    }
}

void Shader::setUniformVec3(const std::string &name, const glm::vec3 &value) {
    GLint location = glGetUniformLocation(m_shaderId, name.c_str());
    if (location != -1) {
        glUniform3fv(location, 1,&value.x);
    } else {
        TK_LOG_W << "Uniform not found: " << name;
    }
}

void Shader::setUniformFloat(const std::string &name, const float &value) {
    GLint location = glGetUniformLocation(m_shaderId, name.c_str());
    if (location != -1) {
        glUniform1f(location, value);
    } else {
        TK_LOG_W << "Uniform not found: " << name;
    }
}


