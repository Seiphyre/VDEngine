#version 330 core

uniform vec3 u_Diffuse_Color;

out vec4 out_FragColor;

void main()
{
    out_FragColor = vec4(u_Diffuse_Color, 1.0);
}
