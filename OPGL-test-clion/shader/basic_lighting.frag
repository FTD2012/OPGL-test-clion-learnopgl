const char *basic_lighting_fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
in vec4 ourPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;
void main()
{
    if (ourPosition.x <= 0.2 ) {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    } else {

        // ambient
        float ambientStrength = 0.1f;
        vec3 ambient = ambientStrength * lightColor;



        FragColor = vec4((ambient) * objectColor, 1.0f);
    }
}
)";
