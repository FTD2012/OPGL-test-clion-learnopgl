const char *material_map_fragmentShaderSource = R"(#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;
in vec4 ourPosition;
in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;
in vec2 TextureCoord;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    if (ourPosition.x <= -1 ) {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    } else {

        // ambient
        vec3 ambient = vec3(1.0f) * light.ambient * texture(material.diffuse, TextureCoord).rgb;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(LightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = light.diffuse * (diff * texture(material.diffuse, TextureCoord).rgb);

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * (spec * (vec3(1.0f) - texture(material.specular, TextureCoord).rgb));

        // Emission Map 放射光贴图
        vec3 emission = texture(material.emission, TextureCoord).rgb;

        FragColor = vec4(ambient + diffuse + specular + emission, 1.0f);
    }
}
)";
