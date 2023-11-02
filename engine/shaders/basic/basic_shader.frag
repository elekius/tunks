#version 330 core

layout(location = 0) out vec4 f_color;

in vec3 v_normal;
in vec3 v_position;
in vec2 v_tex_coord;

//material
uniform vec3 u_diffuse;
uniform vec3 u_specular;
uniform vec3 u_emissive;
uniform float u_shininess;

//light
uniform vec3 u_lightDirection;
uniform vec3 u_lightColor;

//
uniform sampler2D u_diffuse_map;


void main()
{
    vec3 view = normalize(-v_position);
    vec3 normal = normalize(v_normal);

    vec4 diffuseColor = texture(u_diffuse_map,v_tex_coord);
    if(diffuseColor.w < 0.9) {
        discard;
    }

    //reverse so the light directs to the object
    vec3 light = normalize(-u_lightDirection);
    vec3 reflection = reflect(-light,normal);

    vec3 ambient = diffuseColor.xyz * 0.2f;
    vec3 diffuse = u_lightColor *  max(dot(normal,light),0.0f) * diffuseColor.xyz;
    vec3 specular = pow(max(dot(reflection,view),0.000001f),u_shininess) * u_specular;

    f_color = vec4(ambient+diffuse+specular + u_emissive,1.0f);
}