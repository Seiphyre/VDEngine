#version 330 core

in vec2 f_TexCoord;
in vec3 f_Position_World;
in vec3 f_Normal;

uniform vec3      u_Camera_Position;
uniform vec3      u_Light_Position;
uniform vec3      u_Light_Color;
uniform sampler2D u_Diffuse_Map;
uniform vec3      u_Diffuse_Color;
uniform float     u_Shininess;

out vec4 out_FragColor;

void main()
{
    // -- Light Color Calculation --------

    // Ambient Color
    float ambient_intensity = 0.2;
    vec3  ambient_color     = ambient_intensity * u_Light_Color;

    // Diffuse Color
    float diffuse_intensity = 0.7;
    vec3  normal            = normalize(f_Normal);
    vec3  light_dir         = normalize(u_Light_Position - f_Position_World);

    float diffuse_angle = max(dot(normal, light_dir), 0.0);
    vec3  diffuse_color = diffuse_intensity * diffuse_angle * u_Light_Color;

    // Specular Color
    float specular_intensity = 0.9;
    vec3  view_dir           = normalize(u_Camera_Position - f_Position_World);
    vec3  reflect_dir        = reflect(-light_dir, normal);

    float view_reflect_angle = max(dot(view_dir, reflect_dir), 0.0);
    vec3  specular_color     = specular_intensity * pow(view_reflect_angle, u_Shininess) * u_Light_Color;

    // Result
    vec3 light_combined_color = (ambient_color + diffuse_color + specular_color);

    // -- Object Color Calculation --------

    // Texture Color
    vec4 texture_color = texture(u_Diffuse_Map, f_TexCoord);

    vec4 object_combined_color = texture_color * vec4(u_Diffuse_Color, 1.0);

    // -- Result --------------------------
    out_FragColor = object_combined_color * vec4(light_combined_color, 1.0);
}
