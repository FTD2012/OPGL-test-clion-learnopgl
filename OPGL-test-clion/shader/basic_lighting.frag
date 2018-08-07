const char *basic_lighting_fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
in vec4 ourPosition;
in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;
in vec4 Color;
uniform vec3 lightColor;
uniform vec3 viewPos;
void main()
{
    if (ourPosition.x <= -1 ) {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    } else {
        FragColor = Color;
    }
}
)";
