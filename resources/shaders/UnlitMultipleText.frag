#version 330 core

in vec4 Color;
in vec2 TexCoord;

uniform sampler2D uTexture_0;
uniform sampler2D uTexture_1;

out vec4 FragColor;

void main()
{
    // Texture Color
    vec4 texture_color = mix(texture(uTexture_0, TexCoord), texture(uTexture_1, TexCoord), 0.2);

    // -- Result --------------------------
    FragColor = texture_color * Color;
}
