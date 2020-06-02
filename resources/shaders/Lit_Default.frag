#version 330 core

in vec2 f_TexCoord;
in vec3 f_Position_World;
in vec3 f_Normal;

uniform vec3 u_Camera_Position;

// Light
uniform int  u_Light_Type; // 0: DIRECTIONAL 1: SPOT 2: POINT
uniform vec3 u_Light_Color;

uniform vec3 u_Light_Position;
uniform vec3 u_Light_Direction;

uniform float u_Light_Inner_CutOff_Cos;
uniform float u_Light_Outer_CutOff_Cos;

uniform float u_Light_Attenuation_Const;
uniform float u_Light_Attenuation_Linear;
uniform float u_Light_Attenuation_Quad;

// Material
uniform sampler2D u_Diffuse_Map;
uniform vec3      u_Diffuse_Color;
uniform sampler2D u_Specular_Map;
uniform vec3      u_Specular_Color;
uniform float     u_Shininess;

out vec4 out_FragColor;

vec3 calc_directional_light_color(vec3 object_ambient, vec3 object_diffuse, vec3 object_specular);
vec3 calc_point_light_color(vec3 object_ambient, vec3 object_diffuse, vec3 object_specular);
vec3 calc_spot_light_color(vec3 object_ambient, vec3 object_diffuse, vec3 object_specular);

void main()
{
    vec3 object_ambient  = vec3(texture(u_Diffuse_Map, f_TexCoord)) * u_Diffuse_Color;
    vec3 object_diffuse  = vec3(texture(u_Diffuse_Map, f_TexCoord)) * u_Diffuse_Color;
    vec3 object_specular = vec3(texture(u_Specular_Map, f_TexCoord)) * u_Specular_Color;

    // -- Light Color Calculation --------

    vec3 light_combined_color = vec3(0.0, 0.0, 0.0);

    if (u_Light_Type == 0)
        light_combined_color = calc_directional_light_color(object_ambient, object_diffuse, object_specular);
    if (u_Light_Type == 1)
        light_combined_color = calc_spot_light_color(object_ambient, object_diffuse, object_specular);
    if (u_Light_Type == 2)
        light_combined_color = calc_point_light_color(object_ambient, object_diffuse, object_specular);

    // -- Result --------------------------
    out_FragColor = vec4(light_combined_color, 1.0);
}

vec3 calc_directional_light_color(vec3 object_ambient, vec3 object_diffuse, vec3 object_specular)
{
    // Ambient Color
    float ambient_intensity   = 0.2;
    vec3  light_ambient_color = ambient_intensity * u_Light_Color;

    light_ambient_color = light_ambient_color * vec3(object_ambient);

    // Diffuse Color

    float diffuse_intensity = 0.7;
    vec3  normal            = normalize(f_Normal);
    vec3  light_dir         = normalize(-u_Light_Direction); // normalize(u_Light_Position - f_Position_World);

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
    return (light_ambient_color + light_diffuse_color + light_specular_color);
}

vec3 calc_point_light_color(vec3 object_ambient, vec3 object_diffuse, vec3 object_specular)
{
    // Attenuation
    float distance    = length(u_Light_Position - f_Position_World);
    float attenuation = 1.0 / (u_Light_Attenuation_Const + u_Light_Attenuation_Linear * distance +
                               u_Light_Attenuation_Quad * (distance * distance));

    // Ambient Color
    float ambient_intensity   = 0.2;
    vec3  light_ambient_color = ambient_intensity * u_Light_Color;

    light_ambient_color *= attenuation;
    light_ambient_color *= vec3(object_ambient);

    // Diffuse Color

    float diffuse_intensity = 0.7;
    vec3  normal            = normalize(f_Normal);
    vec3  light_dir         = normalize(u_Light_Position - f_Position_World);

    float diffuse_angle       = max(dot(normal, light_dir), 0.0);
    vec3  light_diffuse_color = diffuse_intensity * diffuse_angle * u_Light_Color;

    light_diffuse_color *= attenuation;
    light_diffuse_color *= vec3(object_diffuse);

    // Specular Color
    float specular_intensity = 0.9;
    vec3  view_dir           = normalize(u_Camera_Position - f_Position_World);
    vec3  reflect_dir        = reflect(-light_dir, normal);

    float view_reflect_angle   = max(dot(view_dir, reflect_dir), 0.0);
    vec3  light_specular_color = specular_intensity * pow(view_reflect_angle, u_Shininess) * u_Light_Color;

    light_specular_color *= attenuation;
    light_specular_color *= vec3(object_specular);

    // Result
    return (light_ambient_color + light_diffuse_color + light_specular_color);
}

vec3 calc_spot_light_color(vec3 object_ambient, vec3 object_diffuse, vec3 object_specular)
{
    vec3 normal           = normalize(f_Normal);
    vec3 obj_to_light_dir = normalize(u_Light_Position - f_Position_World);
    vec3 obj_to_view_dir  = normalize(u_Camera_Position - f_Position_World);

    // Ambiant
    float ambient_intensity   = 0.2;
    vec3  light_ambient_color = ambient_intensity * u_Light_Color;

    light_ambient_color *= vec3(object_ambient);

    // Diffuse Color
    float diffuse_intensity = 0.7;

    float diffuse_angle       = max(dot(normal, obj_to_light_dir), 0.0);
    vec3  light_diffuse_color = diffuse_intensity * diffuse_angle * u_Light_Color;

    light_diffuse_color *= vec3(object_diffuse);

    // Specular Color
    float specular_intensity = 0.9;
    vec3  reflect_dir        = reflect(-obj_to_light_dir, normal);

    float view_reflect_angle   = max(dot(obj_to_view_dir, reflect_dir), 0.0);
    vec3  light_specular_color = specular_intensity * pow(view_reflect_angle, u_Shininess) * u_Light_Color;

    light_specular_color *= vec3(object_specular);

    // Attenuation
    float distance    = length(u_Light_Position - f_Position_World);
    float attenuation = 1.0 / (u_Light_Attenuation_Const + u_Light_Attenuation_Linear * distance +
                               u_Light_Attenuation_Quad * (distance * distance));

    light_ambient_color *= attenuation;
    light_diffuse_color *= attenuation;
    light_specular_color *= attenuation;

    // Soft Edges
    float theta     = dot(obj_to_light_dir, normalize(-u_Light_Direction));
    float epsilon   = u_Light_Inner_CutOff_Cos - u_Light_Outer_CutOff_Cos;
    float intensity = clamp((theta - u_Light_Outer_CutOff_Cos) / epsilon, 0.0, 1.0);

    light_diffuse_color *= intensity;
    light_specular_color *= intensity;

    // Result
    return (light_ambient_color + light_diffuse_color + light_specular_color);
}