#include "Shader.hpp"
#include "engine/utils/Log.hpp"

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShader) {
    TK_LOG("Engine") << "Create shader program for vertex: " << vertexShaderPath << " and: " << fragmentShader;
    m_shaderId = createShader(vertexShaderPath, fragmentShader);
    if (m_shaderId == 0) {
        TK_LOG_E("Engine") << "Failed to create shader program.";
    } else {
        TK_LOG("Engine") << "Successfully created shader with id: " << m_shaderId;
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
        TK_LOG_E("Engine") << "Failed to create shader program.";
        return 0;
    }
    GLuint vertexShaderId = compile(vertexShaderSource, GL_VERTEX_SHADER);
    if (vertexShaderId == 0) {
        TK_LOG_E("Engine") << "Failed to compile the vertex shader.";
        glDeleteProgram(program);
        return 0;
    }

    GLuint fragmentShaderId = compile(fragmentShaderSource, GL_FRAGMENT_SHADER);
    if (fragmentShaderId == 0) {
        TK_LOG_E("Engine") << "Failed to compile the fragment shader.";
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
        TK_LOG_E("Engine") << "Shader compilation error: " << message;
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
        TK_LOG_E("Engine") << "Failed to open file: " << path;
        return "";
    }

    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    shaderContent = buffer.str();

    if (shaderContent.empty()) {
        TK_LOG_W("Engine") << "Shader file is empty: " << path;
    } else {
        TK_LOG("Engine") << "Successfully read shader content from file: " << path;
    }

    fileStream.close();

    return shaderContent;
}

GLuint Shader::getShaderId() const {
    return m_shaderId;
}

void Shader::setUniformMatrix4fv(const std::string &name, const glm::mat4 &value) {
    GLint loc = getUniformLocation(name);
    if(loc != 1)  glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);

}

void Shader::setUniformVec3(const std::string &name, const glm::vec3 &value) {
    GLint loc = getUniformLocation(name);
    if(loc != 1) glUniform3fv(loc, 1,&value.x);
}

void Shader::setUniformFloat(const std::string &name, const float &value) {
    GLint loc = getUniformLocation(name);
    if(loc != 1) glUniform1f(loc, value);
}


void Shader::setUniformInt(const std::string &name, const int &value) {
    GLint loc = getUniformLocation(name);
    if(loc != 1) glUniform1i(loc, value);
}
void Shader::setUniformBool(const std::string &name, const bool &value) {
    GLint loc = getUniformLocation(name);
    if(loc != 1) glUniform1i(loc, value ? 1:0);
}

GLint Shader::getUniformLocation(const std::string &name) {
    auto it = m_cachedUniforms.find(name);
    if (it != m_cachedUniforms.end()) {
        return it->second;
    } else {
        GLint location = glGetUniformLocation(m_shaderId, name.c_str());
        if (location != -1) {
            m_cachedUniforms[name] = location;
        } else {
            TK_LOG_W("Engine") << "Uniform not found: " << name;
        }
        return location;
    }
}




