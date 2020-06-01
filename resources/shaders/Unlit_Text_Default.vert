#version 330 core

in vec3 v_Position;
in vec2 v_TexCoord;

uniform mat4 u_ModelMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat;

out vec2 f_TexCoord;

void main()
{
    gl_Position = u_ProjMat * u_ViewMat * u_ModelMat * vec4(v_Position, 1.0);

    f_TexCoord = v_TexCoord;
}
