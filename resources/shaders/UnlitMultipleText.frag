#version 330 core

in vec4 f_Color;
in vec2 f_TexCoord;

uniform sampler2D u_Texture_0;
uniform sampler2D u_Texture_1;

out vec4 out_FragColor;

void main()
{
    // Texture Color
    vec4 texture_color = mix(texture(u_Texture_0, f_TexCoord), texture(u_Texture_1, f_TexCoord), 0.2);

    // -- Result --------------------------
    out_FragColor = texture_color * f_Color;
}
