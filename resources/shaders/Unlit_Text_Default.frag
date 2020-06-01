#version 330 core

in vec2 f_TexCoord;

uniform sampler2D u_Diffuse_Map;

out vec4 out_FragColor;

void main()
{
    out_FragColor = texture(u_Diffuse_Map, f_TexCoord);
}
