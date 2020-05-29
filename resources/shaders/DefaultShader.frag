#version 330 core

in vec4 Color; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

void main()
{
    FragColor = mix (texture(uTexture1, TexCoord), texture(uTexture2, TexCoord), 0.2) * Color;  ;
}
