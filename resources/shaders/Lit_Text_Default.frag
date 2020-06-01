#version 330 core

in vec2 f_TexCoord;
in vec3 f_Position_World;
in vec3 f_Normal;

uniform vec3 u_Camera_Position;

uniform vec3 u_Light_Position;
uniform vec3 u_Light_Color;

uniform sampler2D u_Diffuse_Map;
uniform vec3      u_Diffuse_Color;
uniform sampler2D u_Specular_Map;
uniform vec3      u_Specular_Color;
uniform float     u_Shininess;

out vec4 out_FragColor;

void main()
{
    // -- Light Color Calculation --------

    vec4 object_ambient  = texture(u_Diffuse_Map, f_TexCoord) * vec4(u_Diffuse_Color, 1.0);
    vec4 object_diffuse  = texture(u_Diffuse_Map, f_TexCoord) * vec4(u_Diffuse_Color, 1.0);
    vec4 object_specular = texture(u_Specular_Map, f_TexCoord) * vec4(u_Specular_Color, 1.0);

    // Ambient Color
    float ambient_intensity   = 0.2;
    vec3  light_ambient_color = ambient_intensity * u_Light_Color;

    light_ambient_color = light_ambient_color * vec3(object_ambient);

    // Diffuse Color

    float diffuse_intensity = 0.7;
    vec3  normal            = normalize(f_Normal);
    vec3  light_dir         = normalize(u_Light_Position - f_Position_World);

    float diffuse_angle       = max(dot(normal, light_dir), 0.0);
    vec3  light_diffuse_color = diffuse_intensity * diffuse_angle * u_Light_Color;

    light_diffuse_color = light_diffuse_color * vec3(object_diffuse);

    // Specular Color
    float specular_intensity = 0.9;
    vec3  view_dir           = normalize(u_Camera_Position - f_Position_World);
    vec3  reflect_dir        = reflect(-light_dir, normal);

    float view_reflect_angle   = max(dot(view_dir, reflect_dir), 0.0);
    vec3  light_specular_color = specular_intensity * pow(view_reflect_angle, u_Shininess) * u_Light_Color;

    light_specular_color = light_specular_color * vec3(object_specular);

    // Result
    vec3 light_combined_color = (light_ambient_color + light_diffuse_color + light_specular_color);

    // -- Result --------------------------
    out_FragColor = vec4(light_combined_color, 1.0);
}
