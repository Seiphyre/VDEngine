#version 330 core

in vec4 Color; // the input variable from the vertex shader (same name and same type)
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D uTexture_0;
uniform sampler2D uTexture_1;

void main()
{
    FragColor = mix(texture(uTexture_0, TexCoord), texture(uTexture_1, TexCoord), 0.2) * Color;
}
