const char *color_light_fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
uniform vec3 lightColor;
void main()
{
    FragColor = vec4(lightColor, 0.0f);
}
)";
