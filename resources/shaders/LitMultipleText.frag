#version 330 core

in vec4 f_Color;
in vec2 f_TexCoord;
in vec3 f_Position_World;
in vec3 f_Normal;

uniform vec3      u_Camera_Position;
uniform vec3      u_Light_Position;
uniform vec3      u_Light_Color;
uniform sampler2D u_Texture_0;
uniform sampler2D u_Texture_1;

out vec4 out_FragColor;

void main()
{
    // -- Light Color Calculation --------

    // Ambient Color
    float ambient_strength = 0.2;
    vec3  ambient_color    = ambient_strength * u_Light_Color;

    // Diffuse Color
    vec3 normal    = normalize(f_Normal);
    vec3 light_dir = normalize(u_Light_Position - f_Position_World);

    float diffuse_angle = max(dot(normal, light_dir), 0.0);
    vec3  diffuse_color = diffuse_angle * u_Light_Color;

    // Specular Color
    float specular_strength = 0.5;
    int   shininess         = 64;
    vec3  view_dir          = normalize(u_Camera_Position - f_Position_World);
    vec3  reflect_dir       = reflect(-light_dir, normal);

    float view_reflect_angle = max(dot(view_dir, reflect_dir), 0.0);
    vec3  specular_color     = specular_strength * pow(view_reflect_angle, shininess) * u_Light_Color;

    // Result
    vec3 light_combined_color = (ambient_color + diffuse_color + specular_color);

    // -- Object Color Calculation --------

    // Texture Color
    vec4 texture_color = mix(texture(u_Texture_0, f_TexCoord), texture(u_Texture_1, f_TexCoord), 0.2);

    // Result
    vec4 object_combined_color = texture_color * f_Color;

    // -- Result --------------------------
    out_FragColor = object_combined_color * vec4(light_combined_color, 1.0);
}
