const char *line_fragmentShaderSource = R"(#version 330 core
in vec3 color;
in vec3 position;
out vec4 FragColor;
void main()
{
    // FragColor = vec4(color, 1.0f);
    float z = gl_FragCoord.z * 2.0 - 1.0; // back to NDC
    FragColor = vec4(vec3(1.0f - ((2.0 * 0.1f * 100.0f) / (100.0f + 0.1f - z * (100.0f - 0.1f)))/100.0f) * color, 1.0f);
}
)";
