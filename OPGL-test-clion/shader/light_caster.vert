const char *light_caster_vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoord;
out vec4 ourPosition;
out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;
out vec2 TextureCoord;
uniform vec3 lightPos;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = transform * projection * view * model * vec4(aPos, 1.0f);
    ourPosition = vec4(aPos, 1.0f);
    FragPos = vec3(view * model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(view * model))) * aNormal;
    LightPos = vec3(view * vec4(lightPos, 1.0f));
    TextureCoord = aTextureCoord;
}
)";
