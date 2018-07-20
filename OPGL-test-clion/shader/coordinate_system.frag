const char *coordinate_system_fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixPercent;
void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), mixPercent);
//    FragColor = texture(texture2, vec2(-TexCoord.x, -TexCoord.y));
}
)";