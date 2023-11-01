#version 330 core

layout(location = 0) out vec4 f_color;

in vec3 v_normal;
in vec3 v_position;

void main()
{
    vec3 view = normalize(-v_position);
    vec3 light = normalize(vec3(1.0f,1.0f,1.0f));
    //normalize cause the interpolation of the vertices
    vec3 normal = normalize(v_normal);
    vec3 color = vec3(1.0f,1.0f,1.0f);
    vec3 reflection = reflect(-light,normal);

    vec3 ambient = color * 0.2f;
    vec3 diffuse = max(dot(normal,light),0.0f) * color;
    vec3 specular = pow(max(dot(reflection,view),0.0f),4.0) * color;

    f_color = vec4(ambient+diffuse+specular,1.0f);
}