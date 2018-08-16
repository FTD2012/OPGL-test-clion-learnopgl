const char *cube_vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoord;
layout (location = 3) in vec4 aColor;
out vec4 ourPosition;
out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;
out vec3 LightDir;
out vec3 Color;
out vec2 TexCoords;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
//    ourPosition = vec4(aPos, 1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(model))) * aNormal;
//    LightPos = vec3(vec4(lightPos, 1.0f));
//    LightDir = vec3(vec4(lightDir, 1.0f));
    Color = vec3(aColor);
    TexCoords = aTextureCoord;

}
)";
