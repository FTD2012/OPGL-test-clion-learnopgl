const char *line_fragmentShaderSource = R"(#version 330 core
in vec3 color;
in vec3 position;
out vec4 FragColor;
void main()
{
    FragColor = vec4(color, 1.0f);
}
)";
