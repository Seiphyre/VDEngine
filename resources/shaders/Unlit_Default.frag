#version 330 core

in vec2 f_TexCoord;

uniform sampler2D u_Diffuse_Map;
uniform vec3      u_Diffuse_Color;

out vec4 out_FragColor;

void main()
{
    out_FragColor = vec4(u_Diffuse_Color, 1.0) * texture(u_Diffuse_Map, f_TexCoord);
}
