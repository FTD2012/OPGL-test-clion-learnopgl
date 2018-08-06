const char *basic_lighting_fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
in vec4 ourPosition;
in vec3 FragPos;
in vec3 Normal;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;
void main()
{
    if (ourPosition.x <= -1 ) {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    } else {

        // ambient
        float ambientStrength = 0.3f;
        vec3 ambient = ambientStrength * lightColor;

        // diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = diff * lightColor;

        // specular
        float specularStrength = 1.0f;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
        vec3 specular = spec * lightColor;

        FragColor = vec4((ambient + diffuse + specular) * objectColor, 1.0f);
    }
}
)";
