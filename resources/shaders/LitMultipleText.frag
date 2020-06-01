#version 330 core

in vec4 Color;
in vec2 TexCoord;
in vec3 WorldPosition;
in vec3 Normal;

uniform vec3      uCamera_position;
uniform vec3      uLight_position;
uniform vec3      uLight_color;
uniform sampler2D uTexture_0;
uniform sampler2D uTexture_1;

out vec4 FragColor;

void main()
{
    // -- Light Color Calculation --------

    // Ambient Color
    float ambient_strength = 0.1;
    vec3  ambient_color    = ambient_strength * uLight_color;

    // Diffuse Color
    vec3 normal    = normalize(Normal);
    vec3 light_dir = normalize(uLight_position - WorldPosition);

    float diffuse_angle = max(dot(normal, light_dir), 0.0);
    vec3  diffuse_color = diffuse_angle * uLight_color;

    // Specular Color
    float specular_strength = 0.5;
    int   shininess         = 64;
    vec3  view_dir          = normalize(uCamera_position - WorldPosition);
    vec3  reflect_dir       = reflect(-light_dir, normal);

    float view_reflect_angle = max(dot(view_dir, reflect_dir), 0.0);
    vec3  specular_color     = specular_strength * pow(view_reflect_angle, shininess) * uLight_color;

    // Result
    vec3 light_combined_color = (ambient_color + diffuse_color + specular_color);

    // -- Object Color Calculation --------

    // Texture Color
    vec4 texture_color = mix(texture(uTexture_0, TexCoord), texture(uTexture_1, TexCoord), 0.2);

    // Result
    vec4 object_combined_color = texture_color * Color;

    // -- Result --------------------------
    FragColor = object_combined_color * vec4(light_combined_color, 1.0);
}
