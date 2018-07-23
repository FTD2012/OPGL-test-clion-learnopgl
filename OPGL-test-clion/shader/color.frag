const char *color_fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
in vec4 ourPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;
void main()
{
    if (ourPosition.x <= 0.2 ) {
        FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    } else {
        FragColor = vec4(lightColor * objectColor, 1.0f);
    }
}
)";
