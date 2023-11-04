#version 440 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_tex_coord;
layout(std140) uniform MyMatrices {
    mat4 a_modelMatrices[1];
};

out vec3 v_normal;
out vec3 v_position;
out vec2 v_tex_coord;
uniform mat4 u_CameraViewProj;
//uniform mat4 u_modelViewProj;
//uniform mat4 u_modelView;
//uniform mat4 u_invModelView;

void main() {
//{
//    gl_Position = u_modelViewProj * vec4(a_position, 1.0f);
//    v_normal =  mat3(u_invModelView) * a_normal;
//    v_position = vec3(u_modelView) * vec3(a_position);
//    v_tex_coord = a_tex_coord;
//    v_normal = vec3(1.0f);
//    v_tex_coord = vec2(1.0f);
//    gl_Position = a_modelMatrices[gl_InstanceID] * vec4(a_position,1.0f);
//
////    mat4 invModelView = transpose(inverse(modelView));
////    mat4 modelViewProj = u_CameraViewProj * a_modelMatrix;
////
////    gl_Position = modelViewProj * vec4(a_position, 1.0f);
////    v_normal =  mat3(invModelView) * a_normal;
////    v_position = vec3(modelView) * vec3(a_position);
////    v_tex_coord = a_tex_coord;
//    mat4 modelView = u_CameraView * a_modelMatrices[gl_InstanceID];
//    gl_Position = u_CameraViewProj * vec4(a_position, 1.0);
//    v_normal = mat3(modelView) * a_normal;
//    v_position = vec3(modelView) * a_position;
//    v_tex_coord = a_tex_coord;
// Retrieve the model matrix for this instance

    mat4 modelMatrix = a_modelMatrices[gl_InstanceID];
    mat4 viewProjMatrix = u_CameraViewProj;
    gl_Position = viewProjMatrix * modelMatrix * vec4(a_position, 1.0f);
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    v_normal = normalMatrix * a_normal;
    v_position = vec3(modelMatrix * vec4(a_position, 1.0f));
    v_tex_coord = a_tex_coord;

}

//            glm::mat4 modelView = m_camera->getView() * modelObject->getMatrices()[i];
//            glm::mat4 invModelView = glm::transpose(glm::inverse(modelView));
//            // Set vertex shader uniforms
//            m_shader->setUniformMatrix4fv("u_modelViewProj", m_camera->getViewProj() * model->getMatrix());
//            m_shader->setUniformMatrix4fv("u_modelView", modelView);
//            m_shader->setUniformMatrix4fv("u_invModelView", invModelView);