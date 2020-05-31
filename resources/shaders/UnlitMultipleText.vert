#version 330 core

in vec3 aPosition;
in vec3 aColor;
in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec4 Color;
out vec2 TexCoord;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);

    Color    = vec4(aColor, 1.0f);
    TexCoord = aTexCoord;
}
