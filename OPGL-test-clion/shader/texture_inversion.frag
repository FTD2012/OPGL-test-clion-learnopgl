const char *texture__inversion_fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;
uniform sampler2D texture1;
void main()
{
    FragColor = vec4(vec3(1.0 - texture(texture1, TexCoord)), 1.0);
}
)";
