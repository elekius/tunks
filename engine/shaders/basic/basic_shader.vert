#version 440 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_tex_coord;
layout(std140,binding = 0) uniform MyMatrices {
    mat4 a_modelMatrices[800];
};

out vec3 v_normal;
out vec3 v_position;
out vec2 v_tex_coord;
uniform mat4 u_CameraViewProj;

void main() {
    mat4 modelMatrix = a_modelMatrices[gl_InstanceID];
    mat4 viewProjMatrix = u_CameraViewProj;
    gl_Position = viewProjMatrix * modelMatrix * vec4(a_position, 1.0f);
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    v_normal = normalMatrix * a_normal;
    v_position = vec3(modelMatrix * vec4(a_position, 1.0f));
    v_tex_coord = a_tex_coord;

}