const char *panel_fragmentShaderSource = R"(#version 330 core
in vec3 position;
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.0f);
}
)";
