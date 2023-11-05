

#ifndef TUNKS_UNIFORMBUFFER_HPP
#define TUNKS_UNIFORMBUFFER_HPP


#include <vector>
#include "glm/glm.hpp"
#include <glad/glad.h>
/**
 *
 * @author ChikyuKido
 */
class UniformBuffer {
public:
    virtual ~UniformBuffer();

    void createBuffer();
    void bind();
    void unbind();
    void updateData(const std::vector<glm::mat4> &matrices);
private:
    GLuint m_bufferId;

};

#endif
