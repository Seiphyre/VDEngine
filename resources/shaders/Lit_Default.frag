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

struct Material
{
    sampler2D diffuse_Map;
    vec3      diffuse_Color;

    sampler2D specular_Map;
    vec3      specular_Color;

    float shininess;
};

struct PhongComponent
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define MAX_LIGHTS 16

// Vertex
in vec2 f_TexCoord;
in vec3 f_Position_World;
in vec3 f_Normal;

// Camera
uniform vec3 u_Camera_Position;

// Lights
uniform Light u_Lights[MAX_LIGHTS];
uniform int   u_Lights_Size;

// Material
uniform Material u_Material;

out vec4 out_FragColor;

vec3 calc_directional_light_color(Light light, PhongComponent obj_color);
vec3 calc_point_light_color(Light light, PhongComponent obj_color);
vec3 calc_spot_light_color(Light light, PhongComponent obj_color);

void main()
{
    PhongComponent obj_color;
    obj_color.ambient  = vec3(texture(u_Material.diffuse_Map, f_TexCoord)) * u_Material.diffuse_Color;
    obj_color.diffuse  = vec3(texture(u_Material.diffuse_Map, f_TexCoord)) * u_Material.diffuse_Color;
    obj_color.specular = vec3(texture(u_Material.specular_Map, f_TexCoord)) * u_Material.specular_Color;

    // -- Light Color Calculation --------

    vec3 light_combined_color = vec3(0.0, 0.0, 0.0);

    for (int i = 0; i < u_Lights_Size; i++)
    {
        if (u_Lights[i].type == 0)
            light_combined_color += calc_directional_light_color(u_Lights[i], obj_color);
        if (u_Lights[i].type == 1)
            light_combined_color += calc_spot_light_color(u_Lights[i], obj_color);
        if (u_Lights[i].type == 2)
            light_combined_color += calc_point_light_color(u_Lights[i], obj_color);
    }

    // -- Result --------------------------
    out_FragColor = vec4(light_combined_color, 1.0);
}

vec3 calc_directional_light_color(Light light, PhongComponent obj_color)
{
    // Ambient Color
    float ambient_intensity   = 0.1;
    vec3  light_ambient_color = ambient_intensity * light.color;

    light_ambient_color = light_ambient_color * obj_color.ambient;

    // Diffuse Color

    float diffuse_intensity = 0.7;
    vec3  normal            = normalize(f_Normal);
    vec3  light_dir         = normalize(-light.direction); // normalize(u_Light_Position - f_Position_World);

    float diffuse_angle       = max(dot(normal, light_dir), 0.0);
    vec3  light_diffuse_color = diffuse_intensity * diffuse_angle * light.color;

    light_diffuse_color = light_diffuse_color * obj_color.diffuse;

    // Specular Color
    float specular_intensity = 0.9;
    vec3  view_dir           = normalize(u_Camera_Position - f_Position_World);
    vec3  reflect_dir        = reflect(-light_dir, normal);

    float view_reflect_angle   = max(dot(view_dir, reflect_dir), 0.0);
    vec3  light_specular_color = specular_intensity * pow(view_reflect_angle, u_Material.shininess) * light.color;

    light_specular_color = light_specular_color * obj_color.specular;

    // Result
    return (light_ambient_color + light_diffuse_color + light_specular_color);
}

vec3 calc_point_light_color(Light light, PhongComponent obj_color)
{
    // Attenuation
    float distance    = length(light.position - f_Position_World);
    float attenuation = 1.0 / (light.attenuation_Const + light.attenuation_Linear * distance +
                               light.attenuation_Quad * (distance * distance));

    // Ambient Color
    float ambient_intensity   = 0.1;
    vec3  light_ambient_color = ambient_intensity * light.color;

    light_ambient_color *= attenuation;
    light_ambient_color *= obj_color.ambient;

    // Diffuse Color

    float diffuse_intensity = 0.7;
    vec3  normal            = normalize(f_Normal);
    vec3  light_dir         = normalize(light.position - f_Position_World);

    float diffuse_angle       = max(dot(normal, light_dir), 0.0);
    vec3  light_diffuse_color = diffuse_intensity * diffuse_angle * light.color;

    light_diffuse_color *= attenuation;
    light_diffuse_color *= obj_color.diffuse;

    // Specular Color
    float specular_intensity = 0.9;
    vec3  view_dir           = normalize(u_Camera_Position - f_Position_World);
    vec3  reflect_dir        = reflect(-light_dir, normal);

    float view_reflect_angle   = max(dot(view_dir, reflect_dir), 0.0);
    vec3  light_specular_color = specular_intensity * pow(view_reflect_angle, u_Material.shininess) * light.color;

    light_specular_color *= attenuation;
    light_specular_color *= obj_color.specular;

    // Result
    return (light_ambient_color + light_diffuse_color + light_specular_color);
}

vec3 calc_spot_light_color(Light light, PhongComponent obj_color)
{
    vec3 normal           = normalize(f_Normal);
    vec3 obj_to_light_dir = normalize(light.position - f_Position_World);
    vec3 obj_to_view_dir  = normalize(u_Camera_Position - f_Position_World);

    // Ambiant
    float ambient_intensity   = 0.1;
    vec3  light_ambient_color = ambient_intensity * light.color;

    light_ambient_color *= obj_color.ambient;

    // Diffuse Color
    float diffuse_intensity = 0.7;

    float diffuse_angle       = max(dot(normal, obj_to_light_dir), 0.0);
    vec3  light_diffuse_color = diffuse_intensity * diffuse_angle * light.color;

    light_diffuse_color *= obj_color.diffuse;

    // Specular Color
    float specular_intensity = 0.9;
    vec3  reflect_dir        = reflect(-obj_to_light_dir, normal);

    float view_reflect_angle   = max(dot(obj_to_view_dir, reflect_dir), 0.0);
    vec3  light_specular_color = specular_intensity * pow(view_reflect_angle, u_Material.shininess) * light.color;

    light_specular_color *= obj_color.specular;

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