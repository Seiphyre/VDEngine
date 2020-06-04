#version 330 core

struct Material
{
    sampler2D diffuse_Map;
    vec3      diffuse_Color;

    sampler2D specular_Map;
    vec3      specular_Color;

    float shininess;
};

in vec2 f_TexCoord;

uniform Material u_Material;

out vec4 out_FragColor;

void main()
{
    out_FragColor = vec4(u_Material.diffuse_Color, 1.0) * texture(u_Material.diffuse_Map, f_TexCoord);
}
