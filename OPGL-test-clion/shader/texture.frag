const char *texture_fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;
uniform sampler2D texture1;
void main()
{
    FragColor = texture(texture1, TexCoord);
//    FragColor = texture(texture1, TexCoord);
//    float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
//    FragColor = vec4(average, average, average, 1.0);
}
)";
