const char *line_fragmentShaderSource = R"(#version 330 core
in vec3 color;
in vec3 position;
out vec4 FragColor;
void main()
{
    if (position.x < 0 || position.y < 0 || position.z < 0) {
        FragColor = vec4(1.0f);
    } else {
        FragColor = vec4(color, 1.0f);
    }
}
)";
