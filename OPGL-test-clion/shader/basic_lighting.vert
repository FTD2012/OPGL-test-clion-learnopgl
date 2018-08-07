const char *basic_lighting_vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out vec4 ourPosition;
out vec4 Color;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = transform * projection * view * model * vec4(aPos, 1.0f);
    ourPosition = vec4(aPos, 1.0f);

    // ambient
    float ambientStrength = 0.3f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 Normal = mat3(transpose(inverse(view * model))) * aNormal;
    vec3 norm = normalize(Normal);
    vec3 FragPos = vec3(view * model * vec4(aPos, 1.0f));
    vec3 LightPos = vec3(view * vec4(lightPos, 1.0f));
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * lightColor;

    Color = vec4((ambient + diffuse + specular) * objectColor, 1.0f);
}
)";
