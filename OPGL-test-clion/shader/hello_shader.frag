const char *hello_triangle_fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
in vec4 vertexColor;
void main()
{
    FragColor = vertexColor;
}
)";
