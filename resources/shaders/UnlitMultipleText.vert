#version 330 core

in vec3 aPosition;
in vec3 aNormal;
in vec3 aColor;
in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec4 Color;
out vec2 TexCoord;
out vec3 WorldPosition;
out vec3 Normal;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);

    Color         = vec4(aColor, 1.0f);
    TexCoord      = aTexCoord;
    WorldPosition = vec3(uModel * vec4(aPosition, 1.0));
    Normal        = mat3(transpose(inverse(uModel))) * aNormal;
}
