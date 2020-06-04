#version 330 core

struct Light
{
    int  type; // 0: DIRECTIONAL 1: SPOT 2: POINT
    vec3 color;

    vec3 position;
    vec3 direction;

    float inner_CutOff_Cos;
    float outer_CutOff_Cos;

    float attenuation_Const;
    float attenuation_Linear;
    float attenuation_Quad;
};

#define MAX_LIGHTS 16

in vec2 f_TexCoord;
in vec3 f_Position_World;
in vec3 f_Normal;

uniform vec3 u_Camera_Position;

// Lights
uniform Light u_Lights[MAX_LIGHTS];
uniform int   u_Lights_Size;

// Material
uniform sampler2D u_Diffuse_Map;
uniform vec3      u_Diffuse_Color;
uniform sampler2D u_Specular_Map;
uniform vec3      u_Specular_Color;
uniform float     u_Shininess;

out vec4 out_FragColor;

vec3 calc_directional_light_color(Light light, vec3 object_ambient, vec3 object_diffuse, vec3 object_specular);
vec3 calc_point_light_color(Light light, vec3 object_ambient, vec3 object_diffuse, vec3 object_specular);
vec3 calc_spot_light_color(Light light, vec3 object_ambient, vec3 object_diffuse, vec3 object_specular);

void main()
{
    vec3 object_ambient  = vec3(texture(u_Diffuse_Map, f_TexCoord)) * u_Diffuse_Color;
    vec3 object_diffuse  = vec3(texture(u_Diffuse_Map, f_TexCoord)) * u_Diffuse_Color;
    vec3 object_specular = vec3(texture(u_Specular_Map, f_TexCoord)) * u_Specular_Color;

    // -- Light Color Calculation --------

    vec3 light_combined_color = vec3(0.0, 0.0, 0.0);

    for (int i = 0; i < u_Lights_Size; i++)
    {
        if (u_Lights[i].type == 0)
            light_combined_color +=
                calc_directional_light_color(u_Lights[i], object_ambient, object_diffuse, object_specular);
        if (u_Lights[i].type == 1)
            light_combined_color += calc_spot_light_color(u_Lights[i], object_ambient, object_diffuse, object_specular);
        if (u_Lights[i].type == 2)
            light_combined_color +=
                calc_point_light_color(u_Lights[i], object_ambient, object_diffuse, object_specular);
    }

    // -- Result --------------------------
    out_FragColor = vec4(light_combined_color, 1.0);
}

vec3 calc_directional_light_color(Light light, vec3 object_ambient, vec3 object_diffuse, vec3 object_specular)
{
    // Ambient Color
    float ambient_intensity   = 0.1;
    vec3  light_ambient_color = ambient_intensity * light.color;

    light_ambient_color = light_ambient_color * vec3(object_ambient);

    // Diffuse Color

    float diffuse_intensity = 0.7;
    vec3  normal            = normalize(f_Normal);
    vec3  light_dir         = normalize(-light.direction); // normalize(u_Light_Position - f_Position_World);

    float diffuse_angle       = max(dot(normal, light_dir), 0.0);
    vec3  light_diffuse_color = diffuse_intensity * diffuse_angle * light.color;

    light_diffuse_color = light_diffuse_color * vec3(object_diffuse);

    // Specular Color
    float specular_intensity = 0.9;
    vec3  view_dir           = normalize(u_Camera_Position - f_Position_World);
    vec3  reflect_dir        = reflect(-light_dir, normal);

    float view_reflect_angle   = max(dot(view_dir, reflect_dir), 0.0);
    vec3  light_specular_color = specular_intensity * pow(view_reflect_angle, u_Shininess) * light.color;

    light_specular_color = light_specular_color * vec3(object_specular);

    // Result
    return (light_ambient_color + light_diffuse_color + light_specular_color);
}

vec3 calc_point_light_color(Light light, vec3 object_ambient, vec3 object_diffuse, vec3 object_specular)
{
    // Attenuation
    float distance    = length(light.position - f_Position_World);
    float attenuation = 1.0 / (light.attenuation_Const + light.attenuation_Linear * distance +
                               light.attenuation_Quad * (distance * distance));

    // Ambient Color
    float ambient_intensity   = 0.1;
    vec3  light_ambient_color = ambient_intensity * light.color;

    light_ambient_color *= attenuation;
    light_ambient_color *= vec3(object_ambient);

    // Diffuse Color

    float diffuse_intensity = 0.7;
    vec3  normal            = normalize(f_Normal);
    vec3  light_dir         = normalize(light.position - f_Position_World);

    float diffuse_angle       = max(dot(normal, light_dir), 0.0);
    vec3  light_diffuse_color = diffuse_intensity * diffuse_angle * light.color;

    light_diffuse_color *= attenuation;
    light_diffuse_color *= vec3(object_diffuse);

    // Specular Color
    float specular_intensity = 0.9;
    vec3  view_dir           = normalize(u_Camera_Position - f_Position_World);
    vec3  reflect_dir        = reflect(-light_dir, normal);

    float view_reflect_angle   = max(dot(view_dir, reflect_dir), 0.0);
    vec3  light_specular_color = specular_intensity * pow(view_reflect_angle, u_Shininess) * light.color;

    light_specular_color *= attenuation;
    light_specular_color *= vec3(object_specular);

    // Result
    return (light_ambient_color + light_diffuse_color + light_specular_color);
}

vec3 calc_spot_light_color(Light light, vec3 object_ambient, vec3 object_diffuse, vec3 object_specular)
{
    vec3 normal           = normalize(f_Normal);
    vec3 obj_to_light_dir = normalize(light.position - f_Position_World);
    vec3 obj_to_view_dir  = normalize(u_Camera_Position - f_Position_World);

    // Ambiant
    float ambient_intensity   = 0.1;
    vec3  light_ambient_color = ambient_intensity * light.color;

    light_ambient_color *= vec3(object_ambient);

    // Diffuse Color
    float diffuse_intensity = 0.7;

    float diffuse_angle       = max(dot(normal, obj_to_light_dir), 0.0);
    vec3  light_diffuse_color = diffuse_intensity * diffuse_angle * light.color;

    light_diffuse_color *= vec3(object_diffuse);

    // Specular Color
    float specular_intensity = 0.9;
    vec3  reflect_dir        = reflect(-obj_to_light_dir, normal);

    float view_reflect_angle   = max(dot(obj_to_view_dir, reflect_dir), 0.0);
    vec3  light_specular_color = specular_intensity * pow(view_reflect_angle, u_Shininess) * light.color;

    light_specular_color *= vec3(object_specular);

    // Attenuation
    float distance    = length(light.position - f_Position_World);
    float attenuation = 1.0 / (light.attenuation_Const + light.attenuation_Linear * distance +
                               light.attenuation_Quad * (distance * distance));

    light_ambient_color *= attenuation;
    light_diffuse_color *= attenuation;
    light_specular_color *= attenuation;

    // Soft Edges
    float theta     = dot(obj_to_light_dir, normalize(-light.direction));
    float epsilon   = light.inner_CutOff_Cos - light.outer_CutOff_Cos;
    float intensity = clamp((theta - light.outer_CutOff_Cos) / epsilon, 0.0, 1.0);

    light_diffuse_color *= intensity;
    light_specular_color *= intensity;

    // Result
    return (light_ambient_color + light_diffuse_color + light_specular_color);
}