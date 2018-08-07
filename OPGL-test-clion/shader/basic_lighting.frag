const char *basic_lighting_fragmentShaderSource = R"(#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform Material material;
uniform Light light;

void main()
{
    if (ourPosition.x <= -1 ) {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    } else {

        // ambient
        vec3 ambient = vec3(1.0f) * light.ambient * material.ambient;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(LightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = light.diffuse * (diff * material.diffuse);

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * (spec * material.specular);

        FragColor = vec4((ambient + diffuse + specular) * objectColor, 1.0f);
    }
}
)";
