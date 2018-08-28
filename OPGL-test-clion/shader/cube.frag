const char *cube_fragmentShaderSource = R"(#version 330 core

struct TextureMaterial {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct ColorMaterial {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// 全局光照
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// 点光源
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// 聚光
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 4


in vec3 Normal;
in vec3 Color;
in vec2 TexCoords;
in vec3 FragPos;

out vec4 FragColor;

uniform DirLight dirLight;
uniform TextureMaterial textureMaterial;
uniform ColorMaterial colorMaterial;
uniform int materialType;
uniform vec3 viewPos;

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int pointLightNumber;
uniform bool enableSpotLight;
uniform bool enableDirectionLight;

uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor, float shininess);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor, float shininess);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor, float shininess);

void main()
{

    if (materialType == 1 || materialType == 2) {
        // properties
        float shininess;
        vec3 norm = normalize(Normal), viewDir = normalize(viewPos - FragPos), color, ambientColor, diffuseColor, specularColor, result;

        // use texture as material
        if (materialType == 1) {
            color = Color * vec3(texture(textureMaterial.diffuse, TexCoords));
            ambientColor = vec3(texture(textureMaterial.diffuse, TexCoords));
            diffuseColor = ambientColor;
            specularColor = vec3(texture(textureMaterial.specular, TexCoords));
            shininess = textureMaterial.shininess;
        }
        // use color as material
        else if (materialType == 2) {
            color = Color * colorMaterial.diffuse;
            ambientColor = colorMaterial.ambient;
            diffuseColor = colorMaterial.diffuse;
            specularColor = colorMaterial.specular;
            shininess = colorMaterial.shininess;
        }

        // == =====================================================
        // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
        // For each phase, a calculate function is defined that calculates the corresponding color
        // per lamp. In the main() function we take all the calculated colors and sum them up for
        // this fragment's final color.
        // == =====================================================

        // phase 1: directional lighting
        result = CalcDirLight(dirLight, norm, viewDir, ambientColor, diffuseColor, specularColor, shininess);

        // phase 2: point lights
        for(int i = 0; i < min(pointLightNumber, NR_POINT_LIGHTS); i++) {
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, ambientColor, diffuseColor, specularColor, shininess);
        }

        // phase 3: spot light
        if (enableSpotLight) {
            result += CalcSpotLight(spotLight, norm, FragPos, viewDir, ambientColor, diffuseColor, specularColor, shininess);
        }

        FragColor = vec4(result * color, 1.0f);
    } else {

        FragColor = vec4(Color, 1.0f);

    }

}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor, float shininess) {
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);
    // 镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // 合并结果
    vec3 ambient  = light.ambient  * ambientColor;
    vec3 diffuse  = light.diffuse  * diff * diffuseColor;
    vec3 specular = light.specular * spec * specularColor;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor, float shininess) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * ambientColor;
    vec3 diffuse = light.diffuse * diff * diffuseColor;
    vec3 specular = light.specular * spec * specularColor;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 ambientColor, vec3 diffuseColor, vec3 specularColor, float shininess)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * ambientColor;
    vec3 diffuse = light.diffuse * diff * diffuseColor;
    vec3 specular = light.specular * spec * specularColor;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}

)";
